#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/ast.h"

int main(int argc, char* argv[]) {
	SymbolTable globals;
	
	globals["pi"] = 3.14159;
	globals["x"] = 10.0;

	std::string input;
	std::cout << "TF-Compiler Shell (Type 'exit' to quit)" << std::endl;

	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);

		if (input == "exit") break;
		if (input.empty()) continue;

		// debug commands
		if (input == "view tree") {
			std::cout << "--- Current Variables ---" << std::endl;
			if (globals.empty()) {
				std::cout << "(no variables defined)" << std::endl;
			}
			else {
				for (const auto& [name, value] : globals) {
					std::cout << name << " = " << value << std::endl;
				}
			}
			std::cout << "-------------------------" << std::endl;
		}

		try {
			auto tokens = tokenize(input);
			Parser parser(tokens);

			auto root = parser.parseStatement();
			if (root) {
				double result = root->evaluate(globals);
				std::cout << result << std::endl;
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

	return 0;
}