#pragma once
#include "argnode.hpp"
#include "seqnode.hpp"
#include "symbol.hpp"

class FuncDeclNode : public ASTNode {
public:
    std::string name;
    std::vector<std::unique_ptr<ArgNode>> args;
    std::unique_ptr<TypeNode> returnType;
    std::unique_ptr<SequenceNode> body;

    virtual void check(std::vector<SymbolTable>& tables);
    virtual void print();
};
