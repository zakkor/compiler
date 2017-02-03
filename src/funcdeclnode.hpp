#pragma once
#include "argnode.hpp"
#include "seqnode.hpp"
#include "symbol.hpp"

class FuncDeclNode : public ASTNode {
public:
    std::string name;
    std::vector<ArgNode*> args;
    TypeNode* returnType;
    SequenceNode* body;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
