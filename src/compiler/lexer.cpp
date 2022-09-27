#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <map>

// #include "lexer.h"

namespace Lexer {

	class InvalidNumberLitteral : public std::exception
	{
		const char* what() const throw ()
		{
			return "The number has an invalid litteral";
		}
	};

	class Token {
	public:
		Token(std::string code_to_tokenize) {
			code = code_to_tokenize + END;
			std::cout << code << std::endl;
			doubleQuotesOpen = false;
		}

		void Run() {
			// Iterate through line
			while (index < code.size()) {
				// Iterate until ' ' or end of string
				bool skip = false;
				while (skip != true) {
					skip = GetToken();
					index += 1;
				}
				// Add buffers to tokens
				AddBufferToTokens();
			}
		}

		void PrintTokens() {
			for (std::string iter : tokens)
				std::cout << iter << std::endl;
		}

	private:
		// Input
		std::string code;

		// Going through
		char value;
		char next_value;
		int index;

		// Buffers
		std::string word_buffer;
		std::string num_buffer;
		std::string string_buffer;
		bool doubleQuotesOpen;

		// Output
		std::vector<std::string> tokens;

		// Constants
		const char END = '\n';
		const char SPACE = ' ';
		const char DOUBLE_QUOTE = '"';
		const char POINT = '.';
		const std::string EMPTY_STRING = "";

		char GetToken() {
			value = code[index];
			next_value = code[index + 1];
			if (value == DOUBLE_QUOTE)
				doubleQuotesOpen = !doubleQuotesOpen;
			else if (isdigit(value)) {
				if (doubleQuotesOpen)
					string_buffer += value;
				else
					num_buffer += value;
			}
			else if (value == POINT) {
				if (doubleQuotesOpen)
					string_buffer += value;
				else {
					std::cout << num_buffer.size() << std::endl;
					std::cout << num_buffer << std::endl;
					if (num_buffer.size() > 0 and num_buffer.find(value) == std::string::npos)
						num_buffer += value;
					else
						throw InvalidNumberLitteral();
				}
			}
			else if (value == SPACE or value == END)
				return true;
			else {
				if(!doubleQuotesOpen)
					word_buffer += value;
				else
					string_buffer += value;
			}

			return false;
		}

		void AddBufferToTokens() {
			if (num_buffer != EMPTY_STRING)
				tokens.push_back(num_buffer);
			else if (word_buffer != EMPTY_STRING)
				tokens.push_back(word_buffer);
			else if (string_buffer != EMPTY_STRING)
				tokens.push_back(string_buffer);
		}
	};

	std::vector<std::string> keywords = {
		"int", "double", "char", "bool", "str", "udf", // Types
		"+", "-", "*", "/", "**", // Operators
		"and", "or", "not", "xor", // Booleans operators
		"band", "bor", "bnot", "bxor", // Bits operators
		"for", "while", "do", "in", "break", "continue"
		// https://www.programiz.com/cpp-programming/keywords-identifiers
	};

}

int main()
{
    Lexer::Token lex  = Lexer::Token("Hello 1.23 ");
    lex.Run();
	lex.PrintTokens();
}
