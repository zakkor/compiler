#pragma once
#include "seqnode.hpp"

class IfNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> cond;
    std::unique_ptr<SequenceNode> ifBody, elseBody;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
