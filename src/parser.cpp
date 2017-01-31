#include <stack>
#include <iostream>

#include "parser.hpp"

/// Parses an `expr` as defined in 'syntax.rules', returning an ASTNode*
ASTNode* Parser::parseExpr(std::vector<Token>::iterator& t, const std::string& terminator) {
    std::stack<ASTNode*> nodeStack;
    std::stack<BinaryOP*> opStack;

    for (std::string type = ""; true; ++t) {
        if (t->size() == 0) continue;

        type = t->type();

        if (type == "NUMBER") {
            auto newVar = new VarNode();
            newVar->val = t->param();
            nodeStack.push(newVar);

        } else if (type == "IDENT") {
            auto newVar = new VarNode();
            newVar->name = t->name();
            newVar->val = 0;
            nodeStack.push(newVar);
        } else if (type == "ADD") {
            auto newOp = new OPAddNode();
            opStack.push(newOp);

        } else if (type == "SUB") {
            auto newOp = new OPSubNode();
            opStack.push(newOp);
        } else if (type == terminator) {
            break;
        } else {
            throw SyntacticException("Error: illegal token in expression (" + type + ")\n");
        }
    }

    // merge nodes together
    while (!opStack.empty()) {
        auto op = opStack.top();
        opStack.pop();
        auto lhs = nodeStack.top();
        nodeStack.pop();
        auto rhs = nodeStack.top();
        nodeStack.pop();
        op->lhs = lhs;
        op->rhs = rhs;
        nodeStack.push(op);
    }

    // only one node left in nodeStack now
    auto retNode = nodeStack.top();
    nodeStack.pop();

    consume(t, terminator);

    return retNode;
}

/// Parses an `stmt` as defined in 'syntax.rules', returning an ASTNode*
ASTNode* Parser::parseStatement(std::vector<Token>::iterator& t, const std::string& terminator) {
    auto type = t->type();

    // first token ( IDENT ) or ( KEYIF )
    if (type == "KEYELSE")
        throw SyntacticException("Error: else without a previous if\n");
    if (type != "IDENT" && type != "KEYIF")
        throw SyntacticException("Error: statement must begin with identifier or if (have " + type + ")\n");


    if (type == "IDENT") {
        auto var = new VarNode();
        var->name = t->name();

        consume(t, "IDENT"); // @Error: maybe add detailed error?
        // identifier must be followed by assignment
        auto assign = new AssignNode();
        assign->lhs = var;

        // third token (start of expr ( IDENT|NUMBER ))
        consume(t, "ASSIGN");
        assign->rhs = parseExpr(t, "TERM");
        return assign;
    } else if (type == "KEYIF") {
        auto ifNode = new IfNode();
        consume(t, "KEYIF");

        ASTNode* cond = parseExpr(t, "OBRACE");
        ifNode->cond = cond;

        auto ifBody = new SequenceNode();
        while (t->type() != "CBRACE") {
            ifBody->seq.push_back(parseStatement(t, "CBRACE"));
        }
        ifNode->ifBody = ifBody;

        consume(t, "CBRACE");

        // will be either an ELSE or the next statement
        type = t->type();
        if (type == "KEYELSE") {
            consume(t, "KEYELSE"); // consume KEYELSE
            consume(t, "OBRACE"); // consume OBRACKET

            auto elseBody = new SequenceNode();
            while (t->type() != "CBRACE") {
                elseBody->seq.push_back(parseStatement(t, "CBRACE"));
            }
            ifNode->elseBody = elseBody;

            consume(t, "CBRACE");
        }
    }
}

void Parser::parse(std::vector<Token> tokens) {
    std::cout << "Building AST...";
    root = new SequenceNode();

    for (auto t = tokens.begin(); t != tokens.end(); /* */) {
        root->seq.push_back(parseStatement(t, "TERM"));
    }
    std::cout << " done\n";
}

void Parser::print() {
    ASTNode* node = nullptr;

}
