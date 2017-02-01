#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "token.hpp"
#include "error.hpp"

static unsigned int nn = 0;

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

class TypeNode : public ASTNode {
public:
    TypeNode() : name("?") {}
    std::string name;

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";\n";
        std::cout << cur << "[label=\"Type\\nname=" << name << "\"];" << std::endl;
    }
};

class VarNode : public ASTNode {
public:
    std::string name;
    int val;
    TypeNode* type;

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";\n";
        std::cout << cur << "[label=\"Var\\nname=" << name << ", val=" << val << "\"];" << std::endl;
        std::cout << cur << "--"; type->traverseAndPrint();
    }

    virtual int get() {
        return val;
    }
};

class NumberLiteralNode : public ASTNode {
public:
    int val;

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";\n";
        std::cout << cur << "[label=\"Number literal\\nval=" << val << "\"];" << std::endl;
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

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Add\"];" << std::endl;
        std::cout << cur << "--"; lhs->traverseAndPrint();
        std::cout << cur << "--"; rhs->traverseAndPrint();
    }
};

class OPSubNode : public BinaryOP {
public:
    virtual int get() {
        return rhs->get() - lhs->get();
    }

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Subtract\"];" << std::endl;
        std::cout << cur << "--"; lhs->traverseAndPrint();
        std::cout << cur << "--"; rhs->traverseAndPrint();
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
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Sequence\"];" << std::endl;
        for (auto node : seq) {
            std::cout << cur << "--"; node->traverseAndPrint();
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
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"If\"];" << std::endl;
        std::cout << cur << "--"; cond->traverseAndPrint();

        if (ifBody) {
            std::cout << cur << "--"; ifBody->traverseAndPrint();
        }

        if (elseBody) {
            std::cout << cur << "--"; elseBody->traverseAndPrint();
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

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Assign\"];" << std::endl;
        std::cout << cur << "--"; lhs->traverseAndPrint();
        std::cout << cur << "--"; rhs->traverseAndPrint();
    }
};

class RetNode : public ASTNode {
public:
    ASTNode* toReturn;

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Ret\"];" << std::endl;
        std::cout << cur << "--"; toReturn->traverseAndPrint();
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
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"Decl\"];" << std::endl;
        std::cout << cur << "--"; lhs->traverseAndPrint();
        std::cout << cur << "--"; rhs->traverseAndPrint();
    }
};

class FuncDeclNode : public ASTNode {
public:
    std::string name;
    std::vector<VarNode*> args;
    TypeNode* returnType;
    SequenceNode* body;

    virtual void traverseAndPrint() {
        nn++;
        int cur = nn;
        std::cout << cur << ";" << std::endl;
        std::cout << cur << "[label=\"FuncDecl\\nname=" << name << "\"];" << std::endl;


        if (args.size() > 0) {
            for (auto a : args) {
                std::cout << cur << "--"; a->traverseAndPrint();
            }
        }

        std::cout << cur << "--"; returnType->traverseAndPrint();
        std::cout << cur << "--"; body->traverseAndPrint();
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
