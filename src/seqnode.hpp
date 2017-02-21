#pragma once
#include "astnode.hpp"

class SequenceNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> seq;
    SymbolTable st;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
