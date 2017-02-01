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
        throw -1;
    };
    virtual int get() {
        throw -1;
    };
};

class VarNode : public ASTNode {
public:
    std::string name;
    int val;

    virtual int get() {
        return val;
    }
};

class BinaryOP : public ASTNode {
public:
    ASTNode *lhs, *rhs;
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
};

class AssignNode : public ASTNode {
public:
    VarNode* lhs;
    ASTNode* rhs;
    virtual int get() {
        lhs->val = rhs->get();
        return lhs->val;
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
};
