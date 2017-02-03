#pragma once

#include <iostream>

#include "astnode.hpp"

class VarNode : public ASTNode {
public:
    std::string name;
    int val;

    virtual void print();
    virtual void check(std::vector<SymbolTable>& tables);
};
