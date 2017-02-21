#pragma once

#include "argnode.hpp"
#include "symbol.hpp"

class StructDeclNode : public ASTNode {
public:
    std::string name;
    std::vector<std::unique_ptr<ArgNode>> fields;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
