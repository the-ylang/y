#ifndef __LEXER_H__
#define __LEXER_H__

/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Lexer
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Lex {

	// Exception called when a number has an invalid litteral
	class InvalidNumberLitteral : public std::exception
	{
		std::string m_msg;
	public:
		InvalidNumberLitteral(const std::string num_buffer);
		virtual const char* what() const throw();
	};

	// Lexer class who iterates through the code and returns a list of tokens
	class Lexer {

	public:
		Lexer(std::string code_to_tokenize);

		// Runs the Lexer and add buffers to tokens list
		void Run();

		// Print all tokens (__debug)
		void PrintTokens();

		// Output
		std::vector<std::pair<std::string, int>> tokens;

		// Keywords
		std::vector<std::string> keywords;

	private:
		// The input string (code to tokenize)
		std::string code; // std::string Lexer::code;

		// Going through

		// The actual 
		char value;
		int index;

		// Buffers
		std::string word_buffer;
		std::string num_buffer;
		std::string string_buffer;

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

		char GetToken(std::string* actual_token_buffer, bool* is_number, bool* is_string);

		void AddBufferToTokens();
	};
}

#endif // __LEXER_H__