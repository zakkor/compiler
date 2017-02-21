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
#include "inferdeclnode.hpp"
#include "declnode.hpp"
#include "seqnode.hpp"
#include "ifnode.hpp"
#include "assignnode.hpp"
#include "funcdeclnode.hpp"
#include "retnode.hpp"
#include "unaryops.hpp"
#include "structdeclnode.hpp"

class Parser {
public:
    void parse(std::vector<Token> tokens);
    ASTNode* parseExpr(std::vector<Token>::iterator& t, const std::string& terminator);
    ASTNode* parseStatement(std::vector<Token>::iterator& t, const std::string& terminator);

    static inline void consume(std::vector<Token>::iterator& t, const std::string& requiredType) {
        auto type = t->type();

        auto errorMsg = "illegal token: have '" + type + "', need '"
            + requiredType + "'";

        if (type != requiredType) {
            if (requiredType == "TERM") {
                errorMsg += "\nnote: you are probably missing a semicolon";
            }
            throw SyntacticException(t, errorMsg);
        }

        ++t; // eat token
    }

    void print();
    SequenceNode *root;

    std::vector<Token> tokens;
};
