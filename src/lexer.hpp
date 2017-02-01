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
    Lexer() {
        std::vector<std::pair<std::string, std::string>> staticRules, paramRules;
        paramRules = {
            {R"(\b(?!.*if)(?!.*else)(?!.*return)[^\d\W]+\b)", "IDENT $0"},
            {R"([0-9])", "NUMBER $0"},
        };

        staticRules = {
            {R"(\+)", "ADD"},
            {R"(->)", "HASRET"},
            {R"(\-)", "SUB"},
            {R"(\/)", "DIV"},
            {R"(\*)", "MUL"},
            {R"(\()", "OPAREN"},
            {R"(\))", "CPAREN"},
            {R"((:\=))", "DECL"},
            {R"(\=)", "ASSIGN"},
            {R"(\;)", "TERM"},
            {R"(if)", "KEYIF"},
            {R"(return)", "KEYRET"},
            {R"(\{)", "OBRACE"},
            {R"(\})", "CBRACE"},
            {R"(::)", "HASTYPE"},
            {R"(,)", "COMMA"},
            {R"(else)", "KEYELSE"},
        };

        // order matters
        rules.push_back(paramRules);
        rules.push_back(staticRules);
    }

    void scan(const std::string& filename);
    void print();

    std::vector<std::vector<std::pair<std::string, std::string>>> rules;

    std::vector<Token> tokens;
};
