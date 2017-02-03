#pragma once

#include <exception>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "error.hpp"
#include "symbol.hpp"

#include "astnode.hpp"

bool wasDeclared(std::vector<SymbolTable>& tables, const std::string& name);
std::string findTypeOf(std::vector<SymbolTable>& tables, const std::string& name);

// @Refactor: remove this mess
//static unsigned int nn = 0;



class TypeNode : public ASTNode {
public:
    std::string name;

    virtual void check(std::vector<SymbolTable>& tables) {

    }

    virtual void print() {
        std::cout << currentNode << ";\n";
        std::cout << currentNode << "[label=\"Type\\nname=" << name << "\"];" << std::endl;
    }
};

class VarNode : public ASTNode {
public:
    std::string name;
    int val;

    virtual void print() {
        std::cout << currentNode << ";\n";
        std::cout << currentNode << "[label=\"Var\\nname=" << name << ", val=" << val << "\"];" << std::endl;
    }

    virtual void check(std::vector<SymbolTable>& tables) {
        if (!wasDeclared(tables, name)) {
            throw SemanticException("error: '" + name + "' was not declared in this scope");
        } else {
            /// findTypeOf(tables, name); ///
            // @Typechecking
//            type->name = 
//            type->check(tables);
        }
    }

    virtual int get() {
        return val;
    }
};

class ArgNode : public VarNode {
public:
    TypeNode* type;

    virtual void print() {
        
        std::cout << currentNode << ";\n";
        std::cout << currentNode << "[label=\"Arg\\nname=" << name << ", val=" << val << "\"];" << std::endl;
        std::cout << currentNode << "--"; type->print();
    }
};

class NumberLiteralNode : public ASTNode {
public:
    int val;

    virtual void print() {
        
        std::cout << currentNode << ";\n";
        std::cout << currentNode << "[label=\"Number literal\\nval=" << val << "\"];" << std::endl;
    }

    virtual void check(std::vector<SymbolTable>& tables) {

    }

    virtual std::string getType() {
        return "int";
    }

    virtual int get() {
        return val;
    }
};

class BinaryOP : public ASTNode {
public:
    ASTNode *lhs, *rhs;

    virtual void check(std::vector<SymbolTable>& tables) {
        lhs->check(tables);
        rhs->check(tables);
    }
};

class OPAddNode : public BinaryOP {
public:
    virtual int get() {
        return lhs->get() + rhs->get();
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Add\"];" << std::endl;
        std::cout << currentNode << "--"; lhs->print();
        std::cout << currentNode << "--"; rhs->print();
    }
};

class OPSubNode : public BinaryOP {
public:
    virtual int get() {
        return rhs->get() - lhs->get();
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Subtract\"];" << std::endl;
        std::cout << currentNode << "--"; lhs->print();
        std::cout << currentNode << "--"; rhs->print();
    }
};

class SequenceNode : public ASTNode {
public:
    std::vector<ASTNode*> seq;
    SymbolTable st;

    // contains a sequence of execute()-able nodes (statements)
    virtual void execute() {
        for (auto stmt : seq) {
            stmt->execute();
        }
    }

    virtual void check(std::vector<SymbolTable>& tables) {

        tables.push_back(st);
        for (auto stmt : seq) {
            stmt->check(tables);
        }
        tables.pop_back();

    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Sequence\"];" << std::endl;
        for (auto node : seq) {
            std::cout << currentNode << "--"; node->print();
        }
    }
};

class IfNode : public ASTNode {
public:
    ASTNode *cond;
    SequenceNode *ifBody, *elseBody;

    virtual void execute() {
        if (ifBody && cond->get()) {
            ifBody->execute();
        } else if (elseBody) {
            elseBody->execute();
        }
    }

    virtual void check(std::vector<SymbolTable>& tables) {
        cond->check(tables);
        ifBody->check(tables);
        if (elseBody) {
            elseBody->check(tables);
        }
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"If\"];" << std::endl;
        std::cout << currentNode << "--"; cond->print();

        if (ifBody) {
            std::cout << currentNode << "--"; ifBody->print();
        }

        if (elseBody) {
            std::cout << currentNode << "--"; elseBody->print();
        }
    }
};

class AssignNode : public ASTNode {
public:
    VarNode* lhs;
    ASTNode* rhs;
    virtual int get() {
        lhs->val = rhs->get();
        return lhs->val;
    }

    virtual std::string getAssigneeName() {
        return lhs->name;
    }

    virtual void check(std::vector<SymbolTable>& tables) {
        lhs->check(tables);
        rhs->check(tables);
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Assign\"];" << std::endl;
        std::cout << currentNode << "--"; lhs->print();
        std::cout << currentNode << "--"; rhs->print();
    }
};

class RetNode : public ASTNode {
public:
    ASTNode* toReturn;

    virtual void check(std::vector<SymbolTable>& tables) {
        toReturn->check(tables);
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Ret\"];" << std::endl;
        std::cout << currentNode << "--"; toReturn->print();
    }
};

class DeclNode : public ASTNode {
public:
    VarNode* lhs;
    ASTNode* rhs;
    virtual int get() {
        lhs->val = rhs->get();
        return lhs->val;
    }

    virtual void check(std::vector<SymbolTable>& tables) {
        if (wasDeclared(tables, lhs->name)) {
            throw SemanticException("error: multiple definition of '" + lhs->name + "'");
        } else {
            auto varScope = std::string();
            if (tables.size() == 1) {
                varScope = "global";
            } else {
                varScope = "local";
            }

            tables.back().emplace(std::make_pair(lhs->name, SymbolInfo("var", rhs->getType(), varScope)));
            std::cout << "new var added to table: named " << lhs->name << ", type: "
                      << rhs->getType() << ", scope: " << varScope << "\n";
        }
    }

    virtual void print() {
        
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"Decl\"];" << std::endl;
        std::cout << currentNode << "--"; lhs->print();
        std::cout << currentNode << "--"; rhs->print();
    }
};

class FuncDeclNode : public ASTNode {
public:
    std::string name;
    std::vector<ArgNode*> args;
    TypeNode* returnType;
    SequenceNode* body;

    virtual void check(std::vector<SymbolTable>& tables) {
        if (wasDeclared(tables, name)) {
            throw SemanticException("error: multiple definition of function '" + name + "'");
        } else {
            auto funcScope = std::string();
            if (tables.size() == 1) {
                funcScope = "global";
            } else {
                funcScope = "local"; // this is an error
                // @Improve: Need to handle methods
                throw SemanticException("error: function '" + name + "' can only be declared in the global scope");
            }
            tables.back().emplace(std::make_pair(name, SymbolInfo("func", returnType->name, funcScope)));
            std::cout << "new func added to table: named " << name << ", ret type: "
                      << returnType->name << ", scope: " << funcScope << "\n";
        }

        // make a new scope for the args

        tables.push_back(SymbolTable());

        for (auto a : args) {
            if (wasDeclared(tables, a->name)) {
                throw SemanticException("error: multiple definition of '" + a->name + "'");
            } else {
                tables.back().emplace(std::make_pair(a->name, SymbolInfo("var", a->type->name, "local")));
                std::cout << "new var (arg) added to table: named " << a->name << ", type: "
                          << a->type->name << ", scope: " << "local" << "\n";
            }
        }

        returnType->check(tables);

        body->check(tables);
        tables.pop_back();

    }

    virtual void print() {
        std::cout << currentNode << ";" << std::endl;
        std::cout << currentNode << "[label=\"FuncDecl\\nname=" << name << "\"];" << std::endl;


        if (args.size() > 0) {
            for (auto a : args) {
                std::cout << currentNode << "--"; a->print();
            }
        }

        std::cout << currentNode << "--"; returnType->print();
        std::cout << currentNode << "--"; body->print();
    }
};

class Parser {
public:
    void parse(std::vector<Token> tokens);
    ASTNode* parseExpr(std::vector<Token>::iterator& t, const std::string& terminator);
    ASTNode* parseStatement(std::vector<Token>::iterator& t, const std::string& terminator);

    static inline void consume(std::vector<Token>::iterator& t, const std::string& requiredType) {
        auto type = t->type();
        if (type != requiredType) {
            throw SyntacticException("Error: illegal token: have '" + type + "', need '"
                                     + requiredType + "'\n");
        }

        ++t; // eat token
    }

    void print();
    SequenceNode *root;

    std::vector<Token> tokens;
};
