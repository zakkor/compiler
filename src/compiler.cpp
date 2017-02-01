#include "lexer.hpp"
#include "parser.hpp"

int main() {
    Lexer lex;
    lex.scan("test.ed");
    lex.print();

    Parser par;
    par.parse(lex.tokens);
    std::cout << par.root->seq.size() << " top-level nodes.";
//    par.root->execute();
}
