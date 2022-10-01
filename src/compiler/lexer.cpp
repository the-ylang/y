/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Lexer
*/

#include "lexer.h"
#include "cpp_ext/features.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Lex {

    InvalidNumberLitteral::InvalidNumberLitteral(const std::string num_buffer)
        : m_msg("The number " + num_buffer + " has an invalid litteral")
    {}

    const char* InvalidNumberLitteral::what() const throw() {
        return m_msg.c_str();
    }

    Lexer::Lexer(std::string code_to_tokenize) {
        // Add the end char at the end of code if it is not already there
        if (code_to_tokenize.back() != END)
            code = code_to_tokenize + END;
        else
            code = code_to_tokenize;

        // Initialise all the keywords
        keywords = {
            "int", "double", "byte", "char", "bool", "str", "const", "auto", "udf", // Types
            "+", "-", "*", "/", "%", "**", "<<", "++", "--", // Operators
            "and", "or", "not", "xor", // Booleans operators
            "&", "|", "~", "^", // Bitwise operators
            "loop", "for", "while", "do", "break", "continue", // Loops
            "if", "elsif", "else", "switch", "case", "default", "==", "!=", // Statements
            "class", "typedef", "public", "protected", "private", "self", "super", // Object Oriented
            "try", "catch", "even", "raise", // Errors
            "fn", "return", "yield", // Functions
            "codespace", "use" // Spaces and Imports
            // https://www.programiz.com/cpp-programming/keywords-identifiers
        };
    }

    // Runs the Lexer and add buffers to tokens list
    void Lexer::Run() {
        for (index = 0; index < code.size(); index) {
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

    // Print all tokens (__debug)
    void Lexer::PrintTokens() {
        int cpt = 0;
        for (std::pair<std::string, int> tok : tokens) {
            std::cout << cpt << " " << tok.first << " " << tok.second << std::endl;
            cpt++;
        }
    }

    char Lexer::GetToken(std::string* actual_token_buffer, bool* is_number, bool* is_string) {
        value = code[index];
        *actual_token_buffer += value;
        if (value == DOUBLE_QUOTE) {
            if (*is_number)
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
            if (*is_number)
                throw InvalidNumberLitteral(*actual_token_buffer);
            word_buffer += value;
        }

        return false;
    }

    void Lexer::AddBufferToTokens() {
        if (num_buffer != EMPTY_STRING)
            tokens.push_back(std::make_pair(num_buffer, 0));
        else if (word_buffer != EMPTY_STRING) {
            if (in(keywords, word_buffer))
                tokens.push_back(std::make_pair(word_buffer, 3));
            else
                tokens.push_back(std::make_pair(word_buffer, 1));
        }
        else if (string_buffer != EMPTY_STRING)
            tokens.push_back(std::make_pair(string_buffer, 2));

        num_buffer = EMPTY_STRING; word_buffer = EMPTY_STRING; string_buffer = EMPTY_STRING;
    }

    std::vector<std::string> Lexer::split(std::string string_to_split, char delimiter) {
        std::vector<std::string> splitted_string;
        int index_split = 0;
        std::string buffer;
        for (char iter : string_to_split) {
            if (iter == delimiter) {
                splitted_string.push_back(buffer);
                index_split++;
            }
            else
                buffer += iter;
        }

        return splitted_string;
    }
}