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

    std::unique_ptr<ASTNode>
    parseExpr(std::vector<Token>::iterator& t, const std::string& terminator);

    std::unique_ptr<ASTNode>
    parseStatement(std::vector<Token>::iterator& t, const std::string& terminator);

    void consume(std::vector<Token>::iterator& t, const std::string& requiredType);

    void print();
    std::unique_ptr<SequenceNode> root;

    std::vector<Token> tokens;
};
