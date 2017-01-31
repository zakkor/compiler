#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lexer.hpp"

enum class NodeType {
    Var,
    OPAdd,
};

class ASTNode {
public:
    virtual void execute() {
        throw -1;
    };
    virtual int get() {
        throw -1;
    };
};

class VarNode : public ASTNode {
public:
    VarNode(int val) : val(val) {}

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

class IfNode : public ASTNode {
public:
    IfNode(ASTNode *cond, ASTNode *ifBody, ASTNode *elseBody)
        : cond(cond), ifBody(ifBody), elseBody(elseBody) {}

    ASTNode *cond, *ifBody, *elseBody;

    virtual void execute() {
        if (ifBody && cond->get()) {
            ifBody->execute();
        } else if (elseBody) {
            elseBody->execute();
        }
    }
};

class StartNode : public ASTNode {
public:
    StartNode(ASTNode *next) : next(next) {}
    ASTNode *next;

    virtual int get() {
        return next->get();
    }
};

class Parser {
public:
    void parse(std::vector<Token> tokens);
    ASTNode *root;
};
