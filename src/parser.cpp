#include <stack>
#include <iostream>

#include "parser.hpp"

bool wasDeclared(std::vector<SymbolTable>& tables, const std::string& name) {
    for (auto const& t : tables) {
        if (t.find(name) != t.end()) {
            return true;
        }
    }
    return false;
}

std::string findTypeOf(std::vector<SymbolTable>& tables, const std::string& name) {
    for (auto const& t : tables) {
        auto iter = t.find(name);
        if (iter != t.end()) {
            std::cout << "searched for " << name << " and found it as " << (*iter).second.type << " \n";
            return (*iter).second.type;
        }
    }
    std::cout << "searched for " << name << " but not found\n";

    return "invalid";
}

/// Parses an `expr` as defined in 'syntax.rules', returning an ASTNode*
ASTNode* Parser::parseExpr(std::vector<Token>::iterator& t, const std::string& terminator) {
    std::stack<ASTNode*> nodeStack;
    std::stack<BinaryOP*> opStack;

    for (std::string type = ""; true; ++t) {
        if (t->size() == 0) continue;

        type = t->type();

        if (type == "NUMBER") {
            auto newVar = new NumberLiteralNode();
            newVar->val = t->param();
            nodeStack.push(newVar);

        } else if (type == "IDENT") {
            auto newVar = new VarNode();
//            newVar->type = new TypeNode();
            newVar->name = t->name();
            newVar->val = 0;
            nodeStack.push(newVar);
        } else if (type == "ADD") {
            auto newOp = new OPAddNode();
            opStack.push(newOp);

        } else if (type == "SUB") {
            auto newOp = new OPSubNode();
            opStack.push(newOp);
        } else {
            consume(t, terminator);
            break;
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

    return retNode;
}

/// Parses an `stmt` as defined in 'syntax.rules', returning an ASTNode*
ASTNode* Parser::parseStatement(std::vector<Token>::iterator& t, const std::string& terminator) {
    auto type = t->type();

    // first token ( IDENT ) or ( KEYIF )
    if (type == "KEYELSE")
        throw SyntacticException("Error: else without a previous if\n");
    if (type != "IDENT" && type != "KEYIF" && type != "KEYRET")
        throw SyntacticException("Error: statement must begin with def, decl, return, or if (have " + type + ")\n");


    if (type == "IDENT") {
        auto identName = t->name();

        consume(t, "IDENT");

        // identifier must be followed by
        // assignment | declaration | hastype
        type = t->type();
        if (type == "ASSIGN") {
            auto assign = new AssignNode();
            auto var = new VarNode();
//            var->type = new TypeNode();
            var->name = identName;
            assign->lhs = var;
            consume(t, "ASSIGN");
            assign->rhs = parseExpr(t, "TERM");
            return assign;
        }
        else if (type == "DECL") {
            auto decl = new DeclNode();
            auto var = new VarNode();
//            var->type = new TypeNode();
            var->name = identName;
            decl->lhs = var;
            consume(t, "DECL");
            decl->rhs = parseExpr(t, "TERM");
            return decl;
        }
        // is function
        else if (type == "HASTYPE") {
            consume(t, "HASTYPE");

            auto funcNode = new FuncDeclNode();
            funcNode->name = identName;
            auto returnType = new TypeNode();
            returnType->name = "void";
            funcNode->returnType = returnType;

            // parse optional args + return type
            while (t->type() != "OBRACE") {
                if (t->type() == "HASRET") {
                    consume(t, "HASRET");

                    // get type name //
                    returnType->name = t->name();
                    funcNode->returnType = returnType;

                    consume(t, "IDENT");
                    break;
                }

                if (t->type() == "IDENT") {
                    // get type name //
                    auto argTypeNode = new TypeNode();
                    argTypeNode->name = t->name();

                    // advance
                    consume(t, "IDENT");
                    if (t->type() == "IDENT") {
                        // get arg name //
                        auto argNode = new ArgNode();
                        argNode->name = t->name();
                        argNode->type = argTypeNode;
                        funcNode->args.push_back(argNode);

                        consume(t, "IDENT");
                        // potentially consume a comma if it
                        // is followed by an identifier
                        auto maybeIdent = std::next(t, 1);
                        if (t->type() == "COMMA"
                            && maybeIdent->type() == "IDENT") {
                            consume(t, "COMMA");
                        }
                    }
                }
            }

            consume(t, "OBRACE");

            // parse body
            auto body = new SequenceNode();
            while (t->type() != "CBRACE") {
                body->seq.push_back(parseStatement(t, "CBRACE"));
            }
            funcNode->body = body;

            consume(t, "CBRACE");

            return funcNode;
        }
    }
    else if (type == "KEYIF") {
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

        // there can be no else after this because we have
        // reached the end of the token stream
        if (t == tokens.end()) {
            return ifNode;
        }

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
        return ifNode;
    }
    // @TODO: restrict context(functionBody)
    else if (type == "KEYRET") {
        consume(t, "KEYRET");
        auto retNode = new RetNode();
        retNode->toReturn = parseExpr(t, "TERM");
        return retNode;
    }
}

void Parser::parse(std::vector<Token> tokens) {
    this->tokens = tokens;
    root = new SequenceNode();

    for (auto t = this->tokens.begin(); t != this->tokens.end(); /* */) {
        root->seq.push_back(parseStatement(t, "TERM"));
    }
}

void Parser::print() {
    root->traverseAndPrint();
}
