#include "inferdeclnode.hpp"
#include "error.hpp"

void InferDeclNode::check(std::vector<SymbolTable>& tables) {
    if (wasDeclared(tables, lhs->name)) {
        throw SemanticException("error: multiple definition of '" + lhs->name + "'");
    } else {
        auto varScope = std::string();
        if (tables.size() == 1) {
            varScope = "global";
        } else {
            varScope = "local";
        }

        tables.back().emplace(std::make_pair(lhs->name, SymbolInfo("var", rhs->getType(), varScope)));
//        std::cout << "new var added to table: named " << lhs->name << ", type: "
//                  << rhs->getType() << ", scope: " << varScope << "\n";
    }
}

void InferDeclNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"InferDecl\"];" << std::endl;
    std::cout << currentNode << "--"; lhs->print();
    std::cout << currentNode << "--"; rhs->print();
}
