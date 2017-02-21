#pragma once
#include "astnode.hpp"

class RetNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> toReturn;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
