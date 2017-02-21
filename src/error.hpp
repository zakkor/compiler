#pragma once

#include <stdexcept>
#include "token.hpp"
#include <vector>

class SyntacticException : public std::runtime_error {
public:
    SyntacticException(std::vector<Token>::iterator& t, std::string const& msg) :
        std::runtime_error("Syntactic error at line " + t->line() + ", token " + t->toknum() + ": " + msg + '\n')
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
        // TODO: Add line/token error for semantic errors (need to add token information in AST nodes?)
//        std::runtime_error("Semantic error at line " + t->line() + ", token " + t->toknum() + ": " + msg + '\n')
        std::runtime_error(msg)
        {}
};
