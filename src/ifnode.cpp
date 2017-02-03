#include "ifnode.hpp"
#include <iostream>

void IfNode::check(std::vector<SymbolTable>& tables) {
    cond->check(tables);
    ifBody->check(tables);
    if (elseBody) {
        elseBody->check(tables);
    }
}

void IfNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"If\"];" << std::endl;
    std::cout << currentNode << "--"; cond->print();

    if (ifBody) {
        std::cout << currentNode << "--"; ifBody->print();
    }

    if (elseBody) {
        std::cout << currentNode << "--"; elseBody->print();
    }
}
