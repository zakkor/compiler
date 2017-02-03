#include "symbol.hpp"

#include <iostream>

SymbolInfo::SymbolInfo(std::string kind,
           std::string type,
           std::string scope)
    : kind(kind), type(type), scope(scope) {}

bool wasDeclared(std::vector<SymbolTable>& tables, const std::string& name) {
    for (auto const& t : tables) {
        if (t.find(name) != t.end()) {
            return true;
        }
    }
    return false;
}

std::string findTypeOf(std::vector<SymbolTable>& tables, const std::string& name) {
    for (auto const& t : tables) {
        auto iter = t.find(name);
        if (iter != t.end()) {
            std::cout << "searched for " << name << " and found it as " << (*iter).second.type << " \n";
            return (*iter).second.type;
        }
    }
    std::cout << "searched for " << name << " but not found\n";

    return "invalid";
}
