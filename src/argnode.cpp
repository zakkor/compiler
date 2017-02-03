#include "argnode.hpp"

void ArgNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Arg\\nname=" << name << ", val=" << val << "\"];" << std::endl;
    std::cout << currentNode << "--"; type->print();
}
