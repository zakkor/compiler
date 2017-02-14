#pragma once

#include "astnode.hpp"

class UnaryOP : public ASTNode {
public:
    ASTNode *operand;

    virtual void check(std::vector<SymbolTable>& tables);
};

class OPNotNode : public UnaryOP {
public:
    virtual void print();
};
