#pragma once
#include "varnode.hpp"

class AssignNode : public ASTNode {
public:
    std::unique_ptr<VarNode> lhs;
    std::unique_ptr<ASTNode> rhs;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
