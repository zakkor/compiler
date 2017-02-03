#include "typenode.hpp"

void TypeNode::check(std::vector<SymbolTable>& tables) {

}

void TypeNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Type\\nname=" << name << "\"];" << std::endl;
}
