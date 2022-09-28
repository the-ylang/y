#include <iostream>
#include <string>
#include <vector>

// #include "lexer.h"

namespace Lexer {

	class InvalidNumberLitteral : public std::exception
	{
		std::string m_msg;
	public:

		InvalidNumberLitteral(const std::string num_buffer)
			: m_msg("The number " + num_buffer + " has an invalid litteral")
		{}

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}
	};

	/*class InvalidNumberLitteral : public std::exception
	{
		const char* what() const throw ()
		{
			return "The number has an invalid litteral";
		}
	};*/

	class Token {
	public:
		Token(std::string code_to_tokenize) {
			code = code_to_tokenize + END;
			std::cout << code << std::endl;
		}

		void Run() {
			for(index = 0; index < code.size(); index) {
				// Iterate until ' ' or end of string
				std::string act_token_buffer = EMPTY_STRING; // Buffer for the current token
				bool skip = false;
				bool is_number = false;
				bool is_string = false;
				while (skip != true) {
					skip = GetToken(&act_token_buffer, &is_number, &is_string);
					index += 1;
				}
				// Add buffers to tokens
				AddBufferToTokens();
			}
		}

		void PrintTokens() {
			int cpt = 0;
			for (std::pair<std::string, int> tok : tokens) {
				std::cout << cpt << " " << tok.first << " " << tok.second << std::endl;
				cpt++;
			}
		}

	private:
		// Input
		std::string code;

		// Going through
		char value;
		int index;
		int map_index = 0;

		// Buffers
		std::string word_buffer;
		std::string num_buffer;
		std::string string_buffer;

		// Output
		std::vector<std::pair<std::string, int>> tokens;
		/*
		 Int meaning:
		  > 0: Number
		  > 1: Word
		  > 2: String
		  > ...
		*/

		// Constants
		const char END = '\n';
		const char SPACE = ' ';
		const char DOUBLE_QUOTE = '"';
		const char POINT = '.';
		const std::string EMPTY_STRING = "";

		char GetToken(std::string *actual_token_buffer, bool *is_number, bool *is_string) {
			value = code[index];
			*actual_token_buffer += value;
			if (value == DOUBLE_QUOTE) {
				if(*is_number)
					throw InvalidNumberLitteral(code.substr(index));
				*is_string = !*is_string;
			}
			else if (*is_string)
				string_buffer += value;
			else if (value == SPACE || value == END)
				return true;
			else if (isdigit(value)) {
				num_buffer += value;
				*is_number = true;
			}
			else if (value == POINT) {
				if (num_buffer.size() > 0 && num_buffer.find(value) == std::string::npos)
					num_buffer += value;
				else
					throw InvalidNumberLitteral(*actual_token_buffer);
			}
			else {
				if(*is_number)
					throw InvalidNumberLitteral(*actual_token_buffer);
				word_buffer += value;
			}

			return false;
		}

		void AddBufferToTokens() {
			if (num_buffer != EMPTY_STRING)
				tokens.push_back(std::make_pair(num_buffer, 0));
			else if (word_buffer != EMPTY_STRING)
				tokens.push_back(std::make_pair(word_buffer, 1));
			else if (string_buffer != EMPTY_STRING)
				tokens.push_back(std::make_pair(string_buffer, 2));

			num_buffer = EMPTY_STRING; word_buffer = EMPTY_STRING; string_buffer = EMPTY_STRING;
		}
	};

	std::vector<std::string> keywords = {
		"int", "double", "char", "bool", "str", "const", "udf", // Types
		"+", "-", "*", "/", "%", "**", "=", // Operators
		"and", "or", "not", "xor", // Booleans operators
		"&", "|", "~", "^", // Bitwise operators
		"for", "while", "do", "break", "continue", // Loops
		"if", "elsif", "else", "switch", "case", "default", "==", // Statements
		"class", "typedef", "public", "protected", "private", "self", "super", // Object Oriented
		"try", "catch", "even", "raise", // Errors
		"return", "yield", // Return
		"codespace", "use" // Spaces and Imports
		// https://www.programiz.com/cpp-programming/keywords-identifiers
	};

}

int main()
{
	Lexer::Token lex  = Lexer::Token("Hello 1.23 comment tu vas ? \"ahahah\"");
	lex.Run();
	lex.PrintTokens();
}
