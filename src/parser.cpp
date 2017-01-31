#include "parser.hpp"

#include <stack>

void Parser::parse(std::vector<Token> tokens) {
    std::cout << "Building AST...";
    std::stack<ASTNode*> nodeStack;
    std::stack<BinaryOP*> opStack;
    for (auto t = tokens.begin(); t != tokens.end(); ++t) {
        if (t->size() == 0) continue;

        if (t->type() == "NUMBER") {
            auto newVar = new VarNode(t->param());
            nodeStack.push(newVar);
            continue;
        }
        if (t->type() == "ADD") {
            auto newOp = new OPAddNode();
            opStack.push(newOp);
            continue;
        }
        if (t->type() == "SUB") {
            auto newOp = new OPSubNode();
            opStack.push(newOp);
            continue;
        }
        if (t->type() == "TERM") {
            // evaluate... ?
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
            root = new StartNode(nodeStack.top());
            nodeStack.pop();
        }
    }
    std::cout << " done\n";
}
