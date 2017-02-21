#pragma once

#include "varnode.hpp"
#include "typenode.hpp"

class DeclNode : public ASTNode {
public:
    DeclNode(std::unique_ptr<VarNode> var,
             std::unique_ptr<TypeNode> type);

    std::unique_ptr<VarNode> var;
    std::unique_ptr<TypeNode> type;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
