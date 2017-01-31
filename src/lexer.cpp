#include "lexer.hpp"

size_t Token::size() const {
    if (data == " ") return 0;

    auto n = std::count(data.begin(), data.end(), ' ') + 1; // number of spaces + 1
    return n;
}

std::string Token::operator[](size_t idx) const {
    auto tokenVec = split_string(data, " ");
    return tokenVec[idx];
}

std::string Token::type() const {
    if (this->size() == 0) return "BAD!";
    return (*this)[0];
}

int Token::param() const {
    if (size() < 2) throw -2;

    return std::stoi((*this)[1]);
}

std::string Token::full() const {
    return data;
}

void Lexer::scan(const std::string& filename) {
    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line)) {
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
            newTokenGroup.push_back(Token(stringToken));
        }

        // append to full vec
        tokens.insert(tokens.end(), newTokenGroup.begin(), newTokenGroup.end());
    }
}
