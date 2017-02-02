#pragma once



#include <map>
#include <iostream>

struct SymbolInfo {
public:
    SymbolInfo() = delete;
    SymbolInfo(std::string kind,
               std::string type,
               std::string scope)
        : kind(kind), type(type), scope(scope) {}

    std::string kind; // func | var
    std::string type;
    std::string scope;
};

using SymbolTable = std::map<std::string, SymbolInfo>;

class Analyzer {
public:

};
