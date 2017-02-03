#pragma once
#include "astnode.hpp"

class SequenceNode : public ASTNode {
public:
    std::vector<ASTNode*> seq;
    SymbolTable st;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
