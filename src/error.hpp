#pragma once

#include <stdexcept>

class SyntacticException : public std::runtime_error {
public:
    SyntacticException(std::string const& msg) :
        std::runtime_error(msg)
        {}
};
