#include "astnode.hpp"

#include "error.hpp"

unsigned int ASTNode::TotalNodes = 0;

ASTNode::ASTNode() {
    ASTNode::TotalNodes++;
    currentNode = ASTNode::TotalNodes;
}

void ASTNode::execute() {
    throw ASTException("No execute method");
}

int ASTNode::get() {
    throw ASTException("No get method");
}

void ASTNode::print() {
    throw ASTException("No traverse method");
}

void ASTNode::check(std::vector<SymbolTable>& tables) {
    throw ASTException("No check method");
}

std::string ASTNode::getType() {
    throw ASTException("No type method");
}
