#pragma once

#include "varnode.hpp"
#include "typenode.hpp"

class ArgNode : public VarNode {
public:
    TypeNode* type;

    virtual void print();
};
