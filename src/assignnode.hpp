#pragma once
#include "varnode.hpp"

class AssignNode : public ASTNode {
public:
    VarNode* lhs;
    ASTNode* rhs;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
