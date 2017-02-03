#pragma once

#include "astnode.hpp"
#include <iostream>

class NumberLiteralNode : public ASTNode {
public:
    int val;

    virtual void print();
    virtual void check(std::vector<SymbolTable>& tables);
    virtual std::string getType();
};
