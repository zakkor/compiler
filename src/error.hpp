#pragma once

#include <stdexcept>

class SyntacticException : public std::runtime_error {
public:
    SyntacticException(std::string const& msg) :
        std::runtime_error(msg)
        {}
};

class ASTException : public std::runtime_error {
public:
    ASTException(std::string const& msg) :
        std::runtime_error(msg)
        {}
};

class SemanticException : public std::runtime_error {
public:
    SemanticException(std::string const& msg) :
        std::runtime_error(msg)
        {}
};
