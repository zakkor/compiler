#pragma once
#include "astnode.hpp"

class RetNode : public ASTNode {
public:
    ASTNode* toReturn;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
