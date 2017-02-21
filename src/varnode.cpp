#include "varnode.hpp"
#include "symbol.hpp"
#include "error.hpp"

void VarNode::print() {
    std::cout << currentNode << ";\n";
    std::cout << currentNode << "[label=\"Var\\nname=" << name << "\"];" << std::endl;
}

void VarNode::check(std::vector<SymbolTable>& tables) {
    if (!wasDeclared(tables, name)) {
        throw SemanticException("error: '" + name + "' was not declared in this scope");
    } else {
        /// findTypeOf(tables, name); ///
        // TODO: Typechecking
//            type->name = 
//            type->check(tables);
    }
}
