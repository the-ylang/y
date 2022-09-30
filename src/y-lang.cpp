/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Main File
*/

#include "lexer.h"

#include <string>
#include <vector>


int main() {
	Lexer::Lexer lex = Lexer::Lexer("protected int myInt << 12 ;");
	lex.Run();
	lex.PrintTokens();
}