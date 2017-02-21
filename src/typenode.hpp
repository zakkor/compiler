#pragma once

#include <iostream>

#include "astnode.hpp"

class TypeNode : public ASTNode {
public:
    TypeNode(const std::string& name);
    std::string name;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
