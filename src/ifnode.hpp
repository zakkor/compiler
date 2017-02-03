#pragma once
#include "seqnode.hpp"

class IfNode : public ASTNode {
public:
    ASTNode *cond;
    SequenceNode *ifBody, *elseBody;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
