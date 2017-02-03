#include "seqnode.hpp"
#include <iostream>

void SequenceNode::check(std::vector<SymbolTable>& tables) {
    tables.push_back(st);
    for (auto stmt : seq) {
        stmt->check(tables);
    }
    tables.pop_back();
}

void SequenceNode::print() {
    // don't have any prev node if it's the first one
    if (currentNode > 1) {
        std::cout << currentNode << ";" << std::endl;
    }

    std::cout << currentNode << "[label=\"Sequence\"];" << std::endl;
    for (auto node : seq) {
        std::cout << currentNode << "--"; node->print();
    }
}
