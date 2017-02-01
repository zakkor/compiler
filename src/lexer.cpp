#include "lexer.hpp"

void Lexer::print() {
    std::cout << "Lexer output:\n[\n";
    for (auto tok : tokens) {
        std::cout << tok.full() << std::endl;
    }
    std::cout << "]\n";
}

void Lexer::scan(const std::string& filename) {
    std::ifstream file(filename);

    if (showInput) {
        std::cout << "Input is:\n";
    }

    std::string line;
    while (std::getline(file, line)) {

        if (showInput) {
            std::cout << line << "\n";
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
            newTokenGroup.push_back(Token(stringToken));
        }

        // append to full vec
        tokens.insert(tokens.end(), newTokenGroup.begin(), newTokenGroup.end());
    }
}
