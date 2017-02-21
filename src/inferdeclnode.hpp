#pragma once

#include <memory>

#include "varnode.hpp"

class InferDeclNode : public ASTNode {
public:
    std::unique_ptr<VarNode> lhs;
    std::unique_ptr<ASTNode> rhs;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
