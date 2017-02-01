#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "token.hpp"
#include "error.hpp"

enum class NodeType {
    Var,
    OPAdd,
};

class ASTNode {
public:
    NodeType type;
    virtual void execute() {
        throw ASTException("No execute method");
    };
    virtual int get() {
        throw ASTException("No get method");
    };
    virtual void traverseAndPrint() {
        throw ASTException("No traverse method");
    }
};

class VarNode : public ASTNode {
public:
    std::string name;
    int val;

    virtual void traverseAndPrint() {
        std::cout << "VarNode | name: " << name << " val: " << val << std::endl;
    }

    virtual int get() {
        return val;
    }
};

class BinaryOP : public ASTNode {
public:
    ASTNode *lhs, *rhs;

    virtual void traverseAndPrint() {
        std::cout << "BinaryOP | lhs: "; lhs->traverseAndPrint();
        std::cout << " rhs: "; rhs->traverseAndPrint();
        std::cout << std::endl;
    }
};

class OPAddNode : public BinaryOP {
public:
    virtual int get() {
        return lhs->get() + rhs->get();
    }
};

class OPSubNode : public BinaryOP {
public:
    virtual int get() {
        return rhs->get() - lhs->get();
    }
};

class SequenceNode : public ASTNode {
public:
    std::vector<ASTNode*> seq;

    // contains a sequence of execute()-able nodes (statements)
    virtual void execute() {
        for (auto stmt : seq) {
            stmt->execute();
        }
    }

    virtual void traverseAndPrint() {
        for (auto node : seq) {
            node->traverseAndPrint();
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
    virtual void traverseAndPrint() {
        std::cout << "IfNode | cond: "; cond->traverseAndPrint();
        std::cout << "ifBody: ";
        if (ifBody) {
            ifBody->traverseAndPrint();
        } else {
            std::cout << "ifBody is null\n";
        }
        std::cout << "elseBody: ";
        if (elseBody) {
            elseBody->traverseAndPrint();
        } else {
            std::cout << "elseBody is null\n";
        }
        std::cout << std::endl;
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

    virtual void traverseAndPrint() {
        std::cout << "AssignNode | lhs: "; lhs->traverseAndPrint();
        std::cout << " rhs: "; rhs->traverseAndPrint();
        std::cout << std::endl;
    }
};

class RetNode : public ASTNode {
public:
    ASTNode* toReturn;

    virtual void traverseAndPrint() {
        std::cout << "RetNode | toReturn: "; toReturn->traverseAndPrint();
        std::cout << std::endl;
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

    virtual void traverseAndPrint() {
        std::cout << "DeclNode | lhs: "; lhs->traverseAndPrint();
        std::cout << " rhs: "; rhs->traverseAndPrint();
        std::cout << std::endl;
    }
};

class FuncDeclNode : public ASTNode {
public:
    // pair<type, name>
    std::vector<std::pair<VarNode*, VarNode*>> args;
    VarNode* returnType;
    SequenceNode* body;

    virtual void traverseAndPrint() {
        std::cout << "FuncDeclNode | args: ";
        if (args.size() > 0) {
            for (auto a : args) {
                std::cout << "arg type :";
                a.first->traverseAndPrint();
                std::cout << " arg name: ";
                a.second->traverseAndPrint();
            }
        }

        std::cout << " returnType: ";
        returnType->traverseAndPrint();


        std::cout << " body: ";
        body->traverseAndPrint();

        std::cout << std::endl;
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
