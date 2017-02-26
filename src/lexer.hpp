#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

#include "util.hpp"
#include "token.hpp"

class Lexer {
public:
    Lexer();

    void scan(const std::string& filename, bool printInput, bool shouldPrintTokens);
    void printTokens();

    std::vector<std::vector<std::pair<std::string, std::string>>> rules;
    std::vector<Token> tokens;
};
