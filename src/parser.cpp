#include <stack>
#include <iostream>
#include <memory>

#include "parser.hpp"

/// Parses an `expr` as defined in 'syntax.rules', returning an unique ptr to ASTNode
std::unique_ptr<ASTNode>
Parser::parseExpr(std::vector<Token>::iterator& t, const std::string& terminator) {
    std::stack<std::unique_ptr<ASTNode>> nodeStack;
    std::stack<std::unique_ptr<BinaryOP>> binOpStack;
    std::stack<std::unique_ptr<UnaryOP>> unOpStack;

    // TODO: handle order of operations (and parens)

    for (std::string type = ""; true; ++t) {
        if (t->size() == 0) continue;

        type = t->type();

        // plain ASTNodes
        if (type == "NUMBER") {
            auto newVar = std::make_unique<NumberLiteralNode>();
            newVar->val = t->param();

            nodeStack.push(std::move(newVar));
        } else if (type == "IDENT") {
            // ++t;
            // // function call
            // if (t->type() == "OPAREN") {
            //     std::cout << "ident with oparen after it \n";
            // }

            // // just a variable
            // else {
            //     --t;
            auto newVar = std::make_unique<VarNode>();
            newVar->name = t->name();
//            newVar->val = 0;

            nodeStack.push(std::move(newVar));
//            }
        }
        // binary operators
        else if (type == "ADD") {
            binOpStack.push(std::make_unique<OPAddNode>());
        } else if (type == "SUB") {
            binOpStack.push(std::make_unique<OPSubNode>());
        } else if (type == "EQ") {
            binOpStack.push(std::make_unique<OPEqNode>());
        }
        // unary operators
        else if (type == "NOT") {
            unOpStack.push(std::make_unique<OPNotNode>());
        }
        // end of expression
        else {
            consume(t, terminator);
            break;
        }
    }

    // TODO: Make BinaryOP and UnaryOP children of an `Operator` class
    while (!unOpStack.empty()) {
        auto unaryOp = std::move(unOpStack.top());
        unOpStack.pop();

        unaryOp->operand = std::move(nodeStack.top());
        nodeStack.pop();

        nodeStack.push(std::move(unaryOp));
    }

    // merge nodes together
    while (!binOpStack.empty()) {
        auto binaryOp = std::move(binOpStack.top());
        binOpStack.pop();

        binaryOp->lhs = std::move(nodeStack.top());
        nodeStack.pop();

        binaryOp->rhs = std::move(nodeStack.top());
        nodeStack.pop();

        nodeStack.push(std::move(binaryOp));
    }

    // only one node left in nodeStack now
    auto retNode = std::move(nodeStack.top());
    nodeStack.pop();

    return retNode;
}

/// Parses an `stmt` as defined in 'syntax.rules', returning an unique ptr to ASTNode
std::unique_ptr<ASTNode>
Parser::parseStatement(std::vector<Token>::iterator& t, const std::string& terminator) {
    auto type = t->type();

    // first token ( IDENT ) or ( KEYIF )
    if (type == "KEYELSE")
        throw SyntacticException(t, "else without a previous if");
    if (type != "IDENT" && type != "KEYIF" && type != "KEYRET")
        throw SyntacticException(t, "statement must begin with def, decl, return, or if (have " + type + ")");

    if (type == "IDENT") {
        auto identName = t->name();

        consume(t, "IDENT");

        // identifier must be followed by
        // assignment | declaration | hastype | typeidentifier
        type = t->type();
        if (type == "ASSIGN") {
            auto assign = std::make_unique<AssignNode>();
            assign->lhs = std::make_unique<VarNode>();

            assign->lhs->name = identName;

            consume(t, "ASSIGN");

            assign->rhs = parseExpr(t, "TERM");
            return assign;
        }

        // var declaration
        else if (type == "IDENT") {
            auto decl = std::make_unique<DeclNode>();
            decl->var = std::make_unique<VarNode>();
            decl->type = std::make_unique<TypeNode>();

            decl->var->name = identName;
            decl->type->name = t->name();

            consume(t, "IDENT");
            consume(t, "TERM");
            return decl;
        }
        // inferred var initialization
        else if (type == "INFERDECL") {
            auto inferdecl = std::make_unique<InferDeclNode>();
            inferdecl->lhs = std::make_unique<VarNode>();

            inferdecl->lhs->name = identName;

            consume(t, "INFERDECL");

            inferdecl->rhs = parseExpr(t, "TERM");
            return inferdecl;
        }
        // func or struct
        else if (type == "HASTYPE") {
            consume(t, "HASTYPE");

            // struct
            if (t->type() == "KEYSTRUCT") {
                consume(t, "KEYSTRUCT");
                auto structNode = std::make_unique<StructDeclNode>();
                structNode->name = identName;

                consume(t, "OBRACE");

                // TODO: !!!! Refactor this (need to handle function definitions as well (methods))
                while (t->type() != "CBRACE") {
                    if (t->type() == "IDENT") {
                        // get arg name //
                        auto argNode = std::make_unique<ArgNode>();
                        argNode->name = t->name();

                        // advance
                        consume(t, "IDENT");
                        if (t->type() == "IDENT") {
                            // get type name //
                            argNode->type = std::make_unique<TypeNode>();
                            argNode->type->name = t->name();

                            structNode->fields.push_back(std::move(argNode));

                            consume(t, "IDENT");
                            consume(t, "TERM");
                        }
                    } else {
                        throw SyntacticException(t, "illegal token in struct definition (" + t->type() + ")");
                    }
                }
                // refactor until here

                consume(t, "CBRACE");
                return structNode;
            }
            // function
            else {
                auto funcNode = std::make_unique<FuncDeclNode>();
                funcNode->name = identName;

                funcNode->returnType = std::make_unique<TypeNode>();
                funcNode->returnType->name = "void";

                // TODO: Refactor this (?)
                // parse optional args + return type
                while (t->type() != "OBRACE") {
                    if (t->type() == "HASRET") {
                        consume(t, "HASRET");

                        // get type name //
                        funcNode->returnType->name = t->name();

                        consume(t, "IDENT");
                        break;
                    }

                    if (t->type() == "IDENT") {
                        // get arg name //
                        auto argNode = std::make_unique<ArgNode>();
                        argNode->name = t->name();

                        // advance
                        consume(t, "IDENT");
                        if (t->type() == "IDENT") {
                            // get type name //
                            argNode->type = std::make_unique<TypeNode>();
                            argNode->type->name = t->name();
                            funcNode->args.push_back(std::move(argNode));

                            consume(t, "IDENT");
                            // potentially consume a comma if it
                            // is followed by an identifier
                            auto maybeIdent = std::next(t, 1);
                            if (t->type() == "COMMA"
                                && maybeIdent->type() == "IDENT") {
                                consume(t, "COMMA");
                            }
                        }
                    } else {
                        throw SyntacticException(t, "illegal token in function signature (" + t->type() + ")");
                    }
                }

                consume(t, "OBRACE");

                // parse body
                auto body = std::make_unique<SequenceNode>();
                while (t->type() != "CBRACE") {
                    body->seq.push_back(parseStatement(t, "CBRACE"));
                }
                funcNode->body = std::move(body);

                consume(t, "CBRACE");

                return funcNode;
            }
        }
    }
    else if (type == "KEYIF") {
        consume(t, "KEYIF");
        auto ifNode = std::make_unique<IfNode>();
        ifNode->cond = parseExpr(t, "OBRACE");

        auto ifBody = std::make_unique<SequenceNode>();
        while (t->type() != "CBRACE") {
            ifBody->seq.push_back(parseStatement(t, "CBRACE"));
        }
        ifNode->ifBody = std::move(ifBody);

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

            auto elseBody = std::make_unique<SequenceNode>();
            while (t->type() != "CBRACE") {
                elseBody->seq.push_back(parseStatement(t, "CBRACE"));
            }
            ifNode->elseBody = std::move(elseBody);

            consume(t, "CBRACE");
        }
        return ifNode;
    }
    // @TODO: restrict context(functionBody)
    else if (type == "KEYRET") {
        consume(t, "KEYRET");
        auto retNode = std::make_unique<RetNode>();
        retNode->toReturn = parseExpr(t, "TERM");
        return retNode;
    }
}

void Parser::parse(std::vector<Token> tokens) {
    this->tokens = tokens;
    root = std::make_unique<SequenceNode>();

    for (auto t = this->tokens.begin(); t != this->tokens.end(); /* */) {
        root->seq.push_back(parseStatement(t, "TERM"));
    }
}

void Parser::print() {
    root->print();
}
