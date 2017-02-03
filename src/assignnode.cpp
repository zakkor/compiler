#include "assignnode.hpp"
#include <iostream>

void AssignNode::check(std::vector<SymbolTable>& tables) {
    lhs->check(tables);
    rhs->check(tables);
}

void AssignNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Assign\"];" << std::endl;
    std::cout << currentNode << "--"; lhs->print();
    std::cout << currentNode << "--"; rhs->print();
}
