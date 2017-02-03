#include "retnode.hpp"
#include <iostream>

void RetNode::check(std::vector<SymbolTable>& tables) {
    toReturn->check(tables);
}

void RetNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Ret\"];" << std::endl;
    std::cout << currentNode << "--"; toReturn->print();
}
