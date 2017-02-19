#pragma once

#include "varnode.hpp"

class InferDeclNode : public ASTNode {
public:
    VarNode* lhs;
    ASTNode* rhs;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
