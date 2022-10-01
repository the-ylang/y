/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Main File
*/

#include "compiler/lexer.h"

#include <string>
#include <vector>

int main() {
	Lex::Lexer lex = Lex::Lexer("protected int myInt << 12 ;");
	lex.Run();
	lex.PrintTokens();
}