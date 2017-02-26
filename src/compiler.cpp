#include "lexer.hpp"
#include "parser.hpp"
#include "test.hpp"
#include "tclap/CmdLine.h"

int main(int argc, char** argv) {
    bool input = false;
    bool test = false;
    bool tokens = false;
    bool ast = false;
    try {
        TCLAP::CmdLine cmd("Toy compiler", ' ', "0.1");

        TCLAP::SwitchArg argInput("i","debug_input","Print input that was given", cmd, false);
        TCLAP::SwitchArg argTokens("l","debug_lexer","Print tokens", cmd, false);
        TCLAP::SwitchArg argTest("","test","Run tests", cmd, false);
        TCLAP::SwitchArg argAst("a","debug_ast","Print graphviz representation of AST", cmd, false);

        // Parse the argv array.
        cmd.parse(argc, argv);

        // Get the value parsed by each arg.
        input = argInput.getValue();
        tokens = argTokens.getValue();
        test = argTest.getValue();
        ast = argAst.getValue();
    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    // run all tests then quit
    if (test) {
        Tester tester;
        tester.specify("assign.ed",
                       "decl.ed",
                       "funcargsret.ed", "funcargsvoid.ed",
                       "funcvoidvoid.ed", "if.ed",
                       "ifelse.ed", "nestedif.ed",
                       "functions.ed", "struct.ed", "inferdecl.ed"
                       );
        tester.runAll();
        return 0;
    }

    Lexer lex;
    lex.scan("test.ed", input, tokens);

    // syntactic validation
    Parser par;
    try {
        par.parse(lex.tokens);
    }
    catch (const SyntacticException& e) {
        std::cout << e.what();
        return -1;
    }

    // semantic validation
    std::vector<SymbolTable> tables;
    try {
        par.root->check(tables);
    }
    catch (const SemanticException& e) {
        std::cout << e.what();
        return -2;
    }

    if (ast) {
        par.print();
    }
    // std::cout << "table size: " << tables.size() << std::endl;
    // for (auto t : tables) {
    //     for (auto i : t) {
    //         std::cout << "name: " << i.first << std::endl
    //                   << "\tkind: " << i.second.kind << std::endl
    //                   << "\ttype: " << i.second.type << std::endl
    //                   << "\tscope: " << i.second.scope << std::endl;
    //     }
    // }
}
