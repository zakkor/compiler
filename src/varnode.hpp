#pragma once

#include <iostream>

#include "astnode.hpp"

class VarNode : public ASTNode {
public:
    VarNode(){
        std::cout << "called empty varnode()\n";
    };
    VarNode(const std::string& name);
    std::string name;

    virtual void print();
    virtual void check(std::vector<SymbolTable>& tables);
};
