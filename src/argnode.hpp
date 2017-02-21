#pragma once

#include <memory>

#include "varnode.hpp"
#include "typenode.hpp"

// TODO: is this distinction even needed?
class ArgNode : public VarNode {
public:
    std::unique_ptr<TypeNode> type;

    virtual void print();
};
