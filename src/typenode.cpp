#include "typenode.hpp"

TypeNode::TypeNode(const std::string& name)
    : name(name) {}

void TypeNode::check(std::vector<SymbolTable>& tables) {

}

void TypeNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Type\\nname=" << name << "\"];" << std::endl;
}
