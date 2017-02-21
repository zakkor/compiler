#pragma once

#include "astnode.hpp"
#include <memory>

class UnaryOP : public ASTNode {
public:
    std::unique_ptr<ASTNode> operand;

    virtual void check(std::vector<SymbolTable>& tables);
};

class OPNotNode : public UnaryOP {
public:
    virtual void print();
};
