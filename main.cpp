#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "vyne/lexer/lexer.h"
#include "vyne/parser/parser.h"
#include "vyne/ast/ast.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int main(int argc, char* argv[]) {
	SymbolContainer forest;
	forest["global"] = {};
	
	forest["global"]["pi"] = 3.14159;

	std::string input;

	if (argc > 1) {
		std::string filename = argv[1];

		size_t dotPos = filename.find_last_of(".");
		if (dotPos == std::string::npos || filename.substr(dotPos + 1) != "vy") {
			std::cerr << "Error: File must end in .vy" << "\n";
			return 1;
		}

		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Could not open file: " << filename << "\n";
			return 1;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		const std::string& content = buffer.str();

		auto tokens = tokenize(content);

		Parser parser(tokens);

		try {
			while (parser.peekToken().type != TokenType::End) {
				auto ast = parser.parseStatement();
				if (ast) {
					ast->evaluate(forest);
				}
			}
		} catch (const std::exception& e) {
			std::cerr << "Compilation Error: " << e.what() << "\n";
		}

		return 0;
	}

		std::cout << BOLD << CYAN << "Vyne Interpreter v1.0" << RESET << "\n";
		std::cout << "Type " << RED << "exit" << RESET <<" to quit.\n\n";
		while (true) {
			std::cout << GREEN << ">> " << RESET;
			std::getline(std::cin, input);

			if (input == "exit") break;
			if (input.empty()) continue;

			// debug commands
			if (input == "view tree") {
				std::cout << "--- Current Symbol Forest ---" << "\n";
				bool hasAnyVariables = false;

				for (const auto& [groupName, table] : forest) {
					for (const auto& [varName, val] : table) {
						hasAnyVariables = true;

						if (groupName == "default") {
							std::cout << varName << " = ";
						} else {
							std::cout << groupName << "[" << varName << "] = ";
						}

						val.print(std::cout);
						std::cout << "\n";
					}
				}

				if (!hasAnyVariables) {
					std::cout << "(no variables defined)" << "\n";
				}

				std::cout << "-----------------------------" << "\n";
				continue;
			}

			try {
				auto tokens = tokenize(input);
				Parser parser(tokens);

				auto root = parser.parseStatement();
				if (root) {
					Value result;
					try {
						result = root->evaluate(forest); 
					} 
					catch (const ReturnException& e) {
						result = e.value; 
					}
					
					result.print(std::cout);
					std::cout << "\n";
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << "\n";
			}
	}
	return 0;
}