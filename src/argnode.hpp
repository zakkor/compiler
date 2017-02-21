#pragma once

#include <memory>

#include "varnode.hpp"
#include "typenode.hpp"

class ArgNode : public VarNode {
public:
    std::unique_ptr<TypeNode> type;

    virtual void print();
};
