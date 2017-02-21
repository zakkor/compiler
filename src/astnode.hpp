#pragma once

#include <vector>
#include <memory>

#include "symbol.hpp"

class ASTNode {
public:
    ASTNode();

    virtual void execute();
    virtual int get();
    virtual void print();
    virtual void check(std::vector<SymbolTable>& tables);
    virtual std::string getType();

    static unsigned int TotalNodes;
    unsigned int currentNode;
};
