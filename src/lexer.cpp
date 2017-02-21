#include "lexer.hpp"
#include <iomanip>

Lexer::Lexer(bool showInput) : showInput(showInput) {
    std::vector<std::pair<std::string, std::string>> staticRules, paramRules;

    paramRules = {
        {R"(\b(?!.?if)(?!.?else)(?!.?return)(?!.?struct)[^\d\W]+\b)", "IDENT $0"},
        {R"(\b[0-9]+)", "NUMBER $0"},
    };

    staticRules = {
        {R"(\+)", "ADD"},
        {R"(->)", "HASRET"},
        {R"(\-)", "SUB"},
        {R"(\/)", "DIV"},
        {R"(\*)", "MUL"},
        {R"(==)", "EQ"},
        {R"(!=)", "NOTEQ"},
        {R"(\()", "OPAREN"},
        {R"(\))", "CPAREN"},
        {R"((:\=))", "INFERDECL"},
        {R"(\=)", "ASSIGN"},
        {R"(\;)", "TERM"},
        {R"(if)", "KEYIF"},
        {R"(struct)", "KEYSTRUCT"},
        {R"(return)", "KEYRET"},
        {R"(\{)", "OBRACE"},
        {R"(\})", "CBRACE"},
        {R"(::)", "HASTYPE"},
        {R"(,)", "COMMA"},
        {R"(else)", "KEYELSE"},
        {R"(\!)", "NOT"},
    };

    // order matters
    rules.push_back(paramRules);
    rules.push_back(staticRules);
}

void Lexer::print() {
    std::cout << "Lexer output:\n[\n";
    for (auto tok : tokens) {
        std::cout << tok.full() << std::endl;
    }
    std::cout << "]\n";
    std::cout << "-----------------------------------\n";
}

void Lexer::scan(const std::string& filename) {
    std::ifstream file(filename);

    if (showInput) {
        std::cout << "Input is:\n";
    }

    unsigned int lineNumber = 1, tokNumber = 1;
    std::string line;
    while (std::getline(file, line)) {
        tokNumber = 1;
        if (showInput) {
            std::cout << std::setfill('0') << std::setw(2) << lineNumber << " | " << line << "\n";
        }

        for (auto const& rule : rules) {
            for (auto const& iter : rule) {
                std::regex reg(iter.first);
                line = std::regex_replace(line, reg, iter.second + "\n");
            }
        }

        // split on newline and trim
        auto newStringGroup = split_string(line, "\n");
        std::vector<Token> newTokenGroup;
        for (auto& stringToken : newStringGroup) {
            trim(stringToken);
            if (stringToken == " " || stringToken == "") continue;
            newTokenGroup.push_back(Token(std::to_string(lineNumber) + " " + std::to_string(tokNumber) + " " + stringToken));
            tokNumber++;
        }

        // append to full vec
        tokens.insert(tokens.end(), newTokenGroup.begin(), newTokenGroup.end());

        lineNumber++;
    }
}
