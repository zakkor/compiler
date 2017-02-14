#include "unaryops.hpp"

#include <iostream>

void UnaryOP::check(std::vector<SymbolTable>& tables) {
    operand->check(tables);
}

void OPNotNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Not\"];" << std::endl;
    std::cout << currentNode << "--"; operand->print();
}
