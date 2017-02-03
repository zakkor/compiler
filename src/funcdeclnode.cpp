#include "funcdeclnode.hpp"
#include "error.hpp"

#include <iostream>

void FuncDeclNode::check(std::vector<SymbolTable>& tables) {
    if (wasDeclared(tables, name)) {
        throw SemanticException("error: multiple definition of function '" + name + "'");
    } else {
        auto funcScope = std::string();
        if (tables.size() == 1) {
            funcScope = "global";
        } else {
            funcScope = "local"; // this is an error
            // @Improve: Need to handle methods
            throw SemanticException("error: function '" + name + "' can only be declared in the global scope");
        }
        tables.back().emplace(std::make_pair(name, SymbolInfo("func", returnType->name, funcScope)));
        std::cout << "new func added to table: named " << name << ", ret type: "
                  << returnType->name << ", scope: " << funcScope << "\n";
    }

    // make a new scope for the args

    tables.push_back(SymbolTable());

    for (auto a : args) {
        if (wasDeclared(tables, a->name)) {
            throw SemanticException("error: multiple definition of '" + a->name + "'");
        } else {
            tables.back().emplace(std::make_pair(a->name, SymbolInfo("var", a->type->name, "local")));
            std::cout << "new var (arg) added to table: named " << a->name << ", type: "
                      << a->type->name << ", scope: " << "local" << "\n";
        }
    }

    returnType->check(tables);

    body->check(tables);
    tables.pop_back();
}

void FuncDeclNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"FuncDecl\\nname=" << name << "\"];" << std::endl;


    if (args.size() > 0) {
        for (auto a : args) {
            std::cout << currentNode << "--"; a->print();
        }
    }

    std::cout << currentNode << "--"; returnType->print();
    std::cout << currentNode << "--"; body->print();
}
