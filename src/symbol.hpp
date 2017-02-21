#pragma once

#include <string>
#include <map>
#include <vector>

struct SymbolInfo {
public:
    SymbolInfo() = delete;
    SymbolInfo(std::string kind,
               std::string type,
               std::string scope);

    std::string kind; // func | var | struct | field | arg
    std::string type;
    std::string scope;
};

typedef std::map<std::string, SymbolInfo> SymbolTable;

bool wasDeclared(std::vector<SymbolTable>& tables, const std::string& name);
std::string findTypeOf(std::vector<SymbolTable>& tables, const std::string& name);
