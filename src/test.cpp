#include "test.hpp"
#include "lexer.hpp"
#include "parser.hpp"

bool Tester::runAll() {
    std::cout << "Running all tests...\n";

    for (auto const& filename : testList) {
        std::ifstream file(filename);
        if (!file.good()) {
            std::cout << "Test error: could not find file " << filename << "\n";
            return false;
        }
        std::vector<std::string> test;

        std::string line;
        while (std::getline(file, line)) {
            test.push_back(line);
        }

        try {
            Lexer lex;
            lex.scan(filename, false, false);
            Parser par;
            par.parse(lex.tokens);

            std::vector<SymbolTable> tables;
            par.root->check(tables);
        } catch (SyntacticException& e) {
            std::cout << "Parsing test '" << filename << "' failed: " << e.what() << std::endl;
            return false;
        } catch (SemanticException& e) {
            std::cout << "Semantic test '" << filename << "' failed: " << e.what() << std::endl;
            return false;
        } catch (std::exception& e) {
            std::cout << "Tests failed: " << e.what() << std::endl;
            return false;
        }
    }

    std::cout << testList.size() << "/" << testList.size() << " tests OK.\n";
    return true;
}
