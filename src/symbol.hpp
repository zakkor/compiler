#pragma once

#include <string>
#include <map>

struct SymbolInfo {
public:
    SymbolInfo() = delete;
    SymbolInfo(std::string kind,
               std::string type,
               std::string scope);

    std::string kind; // func | var
    std::string type;
    std::string scope;
};

typedef std::map<std::string, SymbolInfo> SymbolTable;
