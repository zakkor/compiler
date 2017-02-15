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
    Lexer(bool showInput = false);

    void scan(const std::string& filename);
    void print();

    std::vector<std::vector<std::pair<std::string, std::string>>> rules;
    std::vector<Token> tokens;
    bool showInput;
};
