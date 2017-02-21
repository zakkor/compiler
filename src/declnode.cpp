#include "declnode.hpp"
#include "error.hpp"

DeclNode::DeclNode(std::unique_ptr<VarNode> var,
                   std::unique_ptr<TypeNode> type)
    : var(std::move(var)), type(std::move(type))
{}

void DeclNode::check(std::vector<SymbolTable>& tables) {
    if (wasDeclared(tables, var->name)) {
        throw SemanticException("error: multiple definition of '" + var->name + "'");
    } else {
        auto varScope = std::string();
        if (tables.size() == 1) {
            varScope = "global";
        } else {
            varScope = "local";
        }

        tables.back().emplace(std::make_pair(var->name, SymbolInfo("var", type->name, varScope)));
//        std::cout << "new var added to table: named " << var->name << ", type: "
//                  << type->name << ", scope: " << varScope << "\n";
    }
}

void DeclNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"Decl\"];" << std::endl;
    std::cout << currentNode << "--"; var->print();
    std::cout << currentNode << "--"; type->print();
}
