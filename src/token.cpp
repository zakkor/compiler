#include <string>
#include <vector>

#include "token.hpp"
#include "util.hpp"

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

std::string Token::name() const {
    if (this->size() == 0) return "BAD!";
    return (*this)[1];
}

int Token::param() const {
    if (size() < 2) throw -2;

    return std::stoi((*this)[1]);
}

std::string Token::full() const {
    return data;
}
