#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

#include "util.hpp"

class Token {
private:
    std::string data;
public:
    Token(std::string data) : data(data) {}
    size_t size() const;
    std::string operator[](size_t idx) const;
    std::string type() const;
    int param() const;
    std::string full() const;
};

class Lexer {
public:
    Lexer() {
        std::vector<std::pair<std::string, std::string>> staticRules, paramRules;
        paramRules = {
            {R"(\b[^\d\W]+\b)", "IDENT $0"},
            {R"([0-9])", "NUMBER $0"},
        };

        staticRules = {
            {R"(\+)", "ADD"},
            {R"(\-)", "SUB"},
            {R"(\/)", "DIV"},
            {R"(\*)", "MUL"},
            {R"(\()", "OPAREN"},
            {R"(\))", "CPAREN"},
            {R"((:\=))", "DEC"},
            {R"(\=)", "ASSIGN"},
            {R"(\;)", "TERM"},
        };

        // order matters
        rules.push_back(paramRules);
        rules.push_back(staticRules);
    }

    void scan(const std::string& filename);

    std::vector<std::vector<std::pair<std::string, std::string>>> rules;

    std::vector<Token> tokens;
};
