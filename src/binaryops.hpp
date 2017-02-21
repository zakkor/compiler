#pragma once
#include "astnode.hpp"
#include <memory>

class BinaryOP : public ASTNode {
public:
    std::unique_ptr<ASTNode> lhs, rhs;

    virtual void check(std::vector<SymbolTable>& tables);
};

class OPAddNode : public BinaryOP {
public:
    virtual void print();
};

class OPSubNode : public BinaryOP {
public:
    virtual void print();
};

class OPEqNode : public BinaryOP {
public:
    virtual void print();
};
