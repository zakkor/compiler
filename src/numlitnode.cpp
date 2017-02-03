#include "numlitnode.hpp"

void NumberLiteralNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Number literal\\nval=" << val << "\"];" << std::endl;
}

void NumberLiteralNode::check(std::vector<SymbolTable>& tables) {

}

std::string NumberLiteralNode::getType() {
    return "int";
}
