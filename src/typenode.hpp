#pragma once

#include <iostream>

#include "astnode.hpp"

class TypeNode : public ASTNode {
public:
    std::string name;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
