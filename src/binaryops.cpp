#include "binaryops.hpp"
#include <iostream>

void BinaryOP::check(std::vector<SymbolTable>& tables) {
    lhs->check(tables);
    rhs->check(tables);
}

void OPAddNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Add\"];" << std::endl;
    std::cout << currentNode << "--"; lhs->print();
    std::cout << currentNode << "--"; rhs->print();
}

void OPSubNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Subtract\"];" << std::endl;
    std::cout << currentNode << "--"; lhs->print();
    std::cout << currentNode << "--"; rhs->print();
}
