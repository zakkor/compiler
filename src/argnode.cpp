#include "argnode.hpp"

void ArgNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Arg\\nname=" << name << "\"];" << std::endl;
    std::cout << currentNode << "--"; type->print();
}
