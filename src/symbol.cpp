#include "symbol.hpp"

SymbolInfo::SymbolInfo(std::string kind,
           std::string type,
           std::string scope)
    : kind(kind), type(type), scope(scope) {}
