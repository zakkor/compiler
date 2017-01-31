#include "lexer.hpp"
#include "parser.hpp"

int main() {
    Lexer lex;
    lex.scan("test.ed");

    for (auto t : lex.tokens) {
        std::cout << t.full() << std::endl;
    }

    Parser par;
    par.parse(lex.tokens);
    std::cout << "Result: " << par.root->get();
}
