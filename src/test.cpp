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
            lex.scan(filename);
            Parser par;
            par.parse(lex.tokens);
        } catch (SyntacticException& e) {
            std::cout << "Test '" << filename << "' failed: " << e.what() << std::endl;
            return false;
        } catch (std::exception& e) {
            std::cout << "Tests failed: " << e.what() << std::endl;
            return false;
        }
    }

    std::cout << testList.size() << "/" << testList.size() << " tests OK.\n";
    return true;
}
