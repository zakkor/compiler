#include "lexer.hpp"
#include "parser.hpp"
#include "test.hpp"

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "test") {
        Tester tester;
        tester.specify("assign.ed",
                       "decl.ed",
                       "funcargsret.ed", "funcargsvoid.ed",
                       "funcvoidvoid.ed", "if.ed",
                       "ifelse.ed", "nestedif.ed",
                       "functions.ed", "struct.ed", "inferdecl.ed"
                       );
        tester.runAll();
    }
    else {
        Lexer lex(true); // true = print file input
        lex.scan("test.ed");
        std::cout << "-----------------------------------\n";
        //        lex.print();

        Parser par;
        try {
            par.parse(lex.tokens);
        }
        catch (const SyntacticException& e) {
            std::cout << e.what();
            return -1;
        }

        std::vector<SymbolTable> tables;
        try {
            par.root->check(tables);
        }
        catch (const SemanticException& e) {
            std::cout << e.what();
            return -2;
        }

        std::cout << "table size: " << tables.size() << std::endl;
        for (auto t : tables) {
            for (auto i : t) {
                std::cout << "name: " << i.first << std::endl
                          << "\tkind: " << i.second.kind << std::endl
                          << "\ttype: " << i.second.type << std::endl
                          << "\tscope: " << i.second.scope << std::endl;
            }
        }

        std::cout << "-----------------------------------\n";
        par.print();
    }
}
