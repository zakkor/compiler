#pragma once

#include <exception>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "error.hpp"
#include "symbol.hpp"

#include "astnode.hpp"
#include "typenode.hpp"
#include "varnode.hpp"
#include "argnode.hpp"
#include "numlitnode.hpp"
#include "binaryops.hpp"
#include "declnode.hpp"
#include "seqnode.hpp"
#include "ifnode.hpp"
#include "assignnode.hpp"
#include "funcdeclnode.hpp"
#include "retnode.hpp"
#include "unaryops.hpp"

class Parser {
public:
    void parse(std::vector<Token> tokens);
    ASTNode* parseExpr(std::vector<Token>::iterator& t, const std::string& terminator);
    ASTNode* parseStatement(std::vector<Token>::iterator& t, const std::string& terminator);

    static inline void consume(std::vector<Token>::iterator& t, const std::string& requiredType) {
        auto type = t->type();
        if (type != requiredType) {
            throw SyntacticException("(Consume) Error: illegal token: have '" + type + "', need '"
                                     + requiredType + "'\n");
        }

        ++t; // eat token
    }

    void print();
    SequenceNode *root;

    std::vector<Token> tokens;
};
