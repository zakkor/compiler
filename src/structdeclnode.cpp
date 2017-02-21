#include "structdeclnode.hpp"
#include "error.hpp"

#include <iostream>

void StructDeclNode::check(std::vector<SymbolTable>& tables) {
    if (wasDeclared(tables, name)) {
        throw SemanticException("error: multiple definition of struct '" + name + "'");
    } else {
        auto structScope = std::string();
        if (tables.size() == 1) {
            structScope = "global";
        } else {
            structScope = "local"; // this is an error
            // TODO: Need to handle methods
            throw SemanticException("error: struct '" + name + "' can only be declared in the global scope");
        }
        tables.back().emplace(std::make_pair(name, SymbolInfo("struct", "???", structScope)));
        std::cout << "new struct added to table: named " << name << ", scope: " << structScope << "\n";
    }

    // make a new scope for the fields
    tables.push_back(SymbolTable());

    for (auto f : fields) {
        tables.back().emplace(std::make_pair(f->name, SymbolInfo("field", f->type->name, "local")));
        std::cout << "new field added to table: named " << f->name << ", type: "
                  << f->type->name << ", scope: " << "local" << "\n";
    }

    tables.pop_back();
}

void StructDeclNode::print() {
    std::cout << currentNode << ";" << std::endl;
    std::cout << currentNode << "[label=\"StructDecl\\nname=" << name << "\"];" << std::endl;

    if (fields.size() > 0) {
        for (auto f : fields) {
            std::cout << currentNode << "--"; f->print();
        }
    }
    //std::cout << currentNode << "--"; fields->print();
}
