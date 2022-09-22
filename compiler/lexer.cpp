/*
 > Code by Icy
 > Y lang
 > https://github.com/The-Y-Programming-Language/y
 > Lexer
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>

#include "utils.h"

// Types (enums) of all token types

// Type (enum) of all single char token types
typedef enum SingleCharTokenTypes {
    // Single delims (DELIM) ----------------------------------------------------------------

    STT_PAREN_OPEN_DELIM,
    STT_PAREN_CLOSE_DELIM,
    STT_STR_DELIM,
    STT_CHR_DELIM,
    STT_INDEX_OPEN_DELIM,
    STT_INDEX_CLOSE_DELIM,
    STT_FUNCTION_OPEN_DELIM,
    STT_FUNCTION_CLOSE_DELIM,

    // Single char no-close (SYM) ----------------------------------------------------------------

    STT_PTR_SYM,
    STT_EOL_SYM,

    // Single char symbols (SYM) ----------------------------------------------------------------

    STT_GREATER_SYM,
    STT_LESS_SYM,
    STT_FOR_STMT,

    // Operators (OP) ----------------------------------------------------------------

    STT_PLUS_OP,
    STT_MINUS_OP,
    STT_TIMES_OP,
    STT_DIV_OP,
    STT_MODULO_OP,

    // Others (SYM) ----------------------------------------------------------------

    STT_MEMORY_ADDRESS_SYM,
    STT_NO_SYM,
    STT_COMMA_SYM,
    STT_COLON_SYM,
    STT_IS_SYM
} SingleCharTokenType;

// Type (enum) of all multiple chars token types
typedef enum MultipleCharsTokenTypes {
    // Multiple chars delims (DELIM) ----------------------------------------------------------------

    MTT_COMMENT_OPEN_DELIM,
    MTT_COMMENT_CLOSE_DELIM,

    // Multiple chars types (TYP / WRD) ----------------------------------------------------------------
    
    MTT_INT_TYP,
    MTT_DOUBLE_TYP,
    MTT_STR_TYP,
    MTT_BOOL_TYP,
    MTT_CHR_TYP,
    MTT_CONST_TYP,
    MTT_UNTYPED_TYP,

    // Multiple chars symbols (SYM) ----------------------------------------------------------------

    MTT_IS_EQUAL_SYM,
    MTT_ASSIGN_SYM,
    MTT_GREATER_OR_EQU_SYM,
    MTT_LESS_OR_EQU_SYM,

    // Statements (STMT) ----------------------------------------------------------------

    MTT_IF_STMT,
    MTT_ELSEIF_STMT,
    MTT_ELSE_STMT,
    MTT_DO_STMT,
    MTT_WHILE_STMT,
    MTT_FOR_STMT,

    // Operators (OP) ----------------------------------------------------------------

    MTT_PLUS_OP,
    MTT_MINUS_OP,
    MTT_TIMES_OP,
    MTT_DIV_OP
} MultipleCharsTokenType;

// Type (enum) of all variable value token types
typedef enum VariableValueTokenTypes {
    VTT_WORD,
    VTT_NUM
} VariableValueTokenType;

using TokenType = std::variant<SingleCharTokenType, MultipleCharsTokenType, VariableValueTokenTypes>;

// Token type lists ----------------------------------------------------------------

// List of all single char token types
SingleCharTokenType singleCharTokenTypes_list[] = {
    STT_PAREN_OPEN_DELIM,
    STT_PAREN_CLOSE_DELIM,
    STT_STR_DELIM,
    STT_CHR_DELIM,
    STT_INDEX_OPEN_DELIM,
    STT_INDEX_CLOSE_DELIM,
    STT_FUNCTION_OPEN_DELIM,
    STT_FUNCTION_CLOSE_DELIM,

    STT_PTR_SYM,
    STT_EOL_SYM,

    STT_GREATER_SYM,
    STT_LESS_SYM,

    STT_PLUS_OP,
    STT_MINUS_OP,
    STT_TIMES_OP,
    STT_DIV_OP,
    STT_MODULO_OP,

    STT_MEMORY_ADDRESS_SYM,
    STT_NO_SYM,
    STT_COMMA_SYM,
    STT_COLON_SYM,
    STT_IS_SYM
};

// List of all multiple chars token types
MultipleCharsTokenType multipleCharsTokenTypes_list[] = {
    MTT_COMMENT_OPEN_DELIM,
    MTT_COMMENT_CLOSE_DELIM,

    MTT_INT_TYP,
    MTT_DOUBLE_TYP,
    MTT_STR_TYP,
    MTT_BOOL_TYP,
    MTT_CHR_TYP,
    MTT_CONST_TYP,
    MTT_UNTYPED_TYP,

    MTT_IS_EQUAL_SYM,
    MTT_ASSIGN_SYM,
    MTT_GREATER_OR_EQU_SYM,
    MTT_LESS_OR_EQU_SYM,

    MTT_IF_STMT,
    MTT_ELSEIF_STMT,
    MTT_ELSE_STMT,
    MTT_DO_STMT,
    MTT_WHILE_STMT,
    MTT_FOR_STMT
};

// List of all variable value token types
VariableValueTokenType variableValueTokenTypes_list[] = {
    VTT_WORD,
    VTT_NUM
};

// Token lists ----------------------------------------------------------------

std::string singleCharTokens_values_list[] = {
  "(", ")", "\"", "'", "[", "]", "{", "}", ".", ";", ">", "<", "+", "-", "*", "/", "%", "&", "!", ",", ":", "?"
};

std::string multipleCharsTokens_values_list[] = {
  "/*", "*/", "int", "double", "str", "bool", "chr", "const", "udf", "==", "<<", ">=", "<=", "if", "elseif", "else", "do", "while", "for"
};

std::string variableValueTokens_values_list[] = {
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIKJLMNOPQRSTUVWXYZ_", "0123456789"
};

std::vector<std::string> variableValueTokens_values_used_strings_list = {};
std::vector<int> variableValueTokens_values_used_numbers_list = {};

// Token Combinations ----------------------------------------------------------------

// SOON

// Function prototypes ----------------------------------------------------------------

// Insert a single token at the end of token_match map
void InsertToken(SingleCharTokenType token_type, std::string token);
// Insert a single token at the end of token_match map
void InsertToken(MultipleCharsTokenType token_type, std::string token);
// Insert a single token at the end of token_match map
void InsertToken(VariableValueTokenType token_type, std::string token);
// Insert all tokens at the end of token_match map using InsertToken() function
void InsertAllTokens();
// Prints all tokens in token_match map
void PrintTokens();
// Prints all tokens in token_match map of a specific type
void PrintTokens(std::string token_class);
// Tokenize and go along the code
void TokenizeCode(std::string code);

// Token class (for iteration) ----------------------------------------------------------------
class Token {
    public:
        Token(std::string code) {
            code_to_tokenize = split(code, ' ');
        }

        void run() {
            bool success;
            for(std::string tokenizing : code_to_tokenize) {
                std::cout << ".........\nTokenizing: '" << tokenizing << "'" << std::endl;
                if(tokenizing.size() == 1) {
                    get_singlechar_token(tokenizing, &success);
                    if(!success) {
                        get_variablevalue_token(tokenizing, &success);
                        if(!success)
                            throw std::runtime_error("Invalid token");
                    }
                }
                else {
                    get_multiplechars_token(tokenizing, &success);
                    if(!success) {
                        get_variablevalue_token(tokenizing, &success);
                        if(!success) {
                            get_singlechar_token_in_multiplechar(tokenizing, &success);
                            if(!success)
                                throw std::runtime_error("Invalid token");
                        }
                    }
                }
            }
            for(std::string temp : all_tokens_strings) {
                std::cout << temp << std::endl;
            }
            std::cout << sizeof(all_tokens) / sizeof(all_tokens[0]) << std::endl;
        }

        void get_singlechar_token(std::string token, bool *success) {
            for(int i = 0; i < sizeof(singleCharTokens_values_list) / sizeof(singleCharTokens_values_list[0]); i++) {
                std::cout << "Is \"" << token << "\" equal to \"" << singleCharTokens_values_list[i] << "\"?" << std::endl;
                if(token == singleCharTokens_values_list[i]) {
                    InsertToken(singleCharTokenTypes_list[i], token);
                    *success = true;
                    all_tokens_strings.push_back(token);
                    std::cout << token << " is in !" << std::endl;
                    return;
                }
            }
            *success = false;
        }

        void get_multiplechars_token(std::string token, bool *success) {
            for(int i = 0; i < sizeof(multipleCharsTokens_values_list) / sizeof(multipleCharsTokens_values_list[0]); i++) {
                std::cout << "Is \"" << token << "\" equal to \"" << multipleCharsTokens_values_list[i] << "\"?" << std::endl;
                if(token == multipleCharsTokens_values_list[i]) {
                    InsertToken(multipleCharsTokenTypes_list[i], token);
                    *success = true;
                    all_tokens_strings.push_back(token);
                    return;
                }
            }
            *success = false;
        }

        void get_variablevalue_token(std::string token, bool *success) {
            if(isNumber(token)) {
                all_tokens.insert(all_tokens.end(), VTT_NUM);
                variableValueTokens_values_used_numbers_list.insert(variableValueTokens_values_used_numbers_list.end(), std::stoi(token));
                std::cout << "Added to variablevalue token list " << token << std::endl;
                *success = true;
                all_tokens_strings.push_back(token);
                return;
            }
            else if(isWord(token)) {
                all_tokens.insert(all_tokens.end(), VTT_WORD);
                variableValueTokens_values_used_strings_list.insert(variableValueTokens_values_used_strings_list.end(), token);
                std::cout << "Added to variablevalue token list " << token << std::endl;
                *success = true;
                all_tokens_strings.push_back(token);
                return;
            }
            else {
                std::cout << "Error: " << token << " is not a valid variable value token" << std::endl;
                *success = false;
                all_tokens_strings.push_back(token);
                return;
            }
            *success = false;
        }

        void get_singlechar_token_in_multiplechar(std::string token, bool *success) {
            for(char chr : token) {
                std::cout << chr << std::endl;
                get_singlechar_token(std::string(1, chr), success);
            }
        }

        void print_tokens() {
            for(int i = 0; i < all_tokens.size(); i++) {
                try {
                    std::cout << std::get<SingleCharTokenType>(all_tokens[i]);
                }
                catch(...) {
                    try {
                        std::cout << std::get<MultipleCharsTokenType>(all_tokens[i]);
                    }
                    catch(...) {
                        try {
                            std::cout << std::get<VariableValueTokenType>(all_tokens[i]);
                        }
                        catch(const std::bad_variant_access& e) {
                            std::cout << "Error: Token type not found" << std::endl;
                            std::cout << e.what() << std::endl;
                        }
                    }
                }
            }
        }

    private:
        // The code to tokenize
        std::vector<std::string> code_to_tokenize;
        // The vector of all tokens found
        std::vector<TokenType> all_tokens;
        // The vector of all string tokens found
        std::vector<std::string> all_tokens_strings;
};

// Main variables declaration ----------------------------------------------------------------

// Map of matches between token types and tokens (single char)
std::map<SingleCharTokenType, std::string> single_char_token_match;
// Map of matches between token types and tokens (multiple chars)
std::map<MultipleCharsTokenType, std::string> multiple_chars_token_match;
// Map of matches between token types and tokens (variable value)
std::map<VariableValueTokenType, std::string> variable_value_token_match;

// Main function ----------------------------------------------------------------

int main()
{
    InsertAllTokens();
    // PrintTokens();
    TokenizeCode("int a << 8");
    TokenizeCode("udf temp << [6, 7, 8]");
    std::cout << "Tokenizing code finished" << std::endl;
    return 0;
}

// Functions bodies ----------------------------------------------------------------

// InsertToken
void InsertToken(SingleCharTokenType token_type, std::string token) {
    single_char_token_match.insert(std::pair<SingleCharTokenType, std::string>(token_type, token));
}
void InsertToken(MultipleCharsTokenType token_type, std::string token) {
    multiple_chars_token_match.insert(std::pair<MultipleCharsTokenType, std::string>(token_type, token));
}
void InsertToken(VariableValueTokenType token_type, std::string token) {
    variable_value_token_match.insert(std::pair<VariableValueTokenType, std::string>(token_type, token));
}

// InsertAllTokens
void InsertAllTokens() {
    for(int i = 0; i < sizeof(singleCharTokenTypes_list) / sizeof(singleCharTokenTypes_list[0]); i++) {
        InsertToken(singleCharTokenTypes_list[i], singleCharTokens_values_list[i]);
    }
    for(int i = 0; i < sizeof(multipleCharsTokenTypes_list) / sizeof(multipleCharsTokenTypes_list[0]); i++) {
        InsertToken(multipleCharsTokenTypes_list[i], multipleCharsTokens_values_list[i]);
    }
    for(int i = 0; i < sizeof(variableValueTokenTypes_list) / sizeof(variableValueTokenTypes_list[0]); i++) {
        InsertToken(variableValueTokenTypes_list[i], variableValueTokens_values_list[i]);
    }
}

// PrintTokens
void PrintTokens() {
    std::map<SingleCharTokenType, std::string>::iterator itr;
    std::cout << "Single char tokens:" << std::endl;
    for(itr=single_char_token_match.begin();itr!=single_char_token_match.end();itr++)
    {
        std::cout<<itr->first<<" "<<itr->second<<std::endl;
    }
    std::map<MultipleCharsTokenType, std::string>::iterator jtr;
    std::cout << "Multiple chars tokens:" << std::endl;
    for(jtr=multiple_chars_token_match.begin();jtr!=multiple_chars_token_match.end();jtr++)
    {
        std::cout<<jtr->first<<" "<<jtr->second<<std::endl;
    }
    std::map<VariableValueTokenType, std::string>::iterator ktr;
    std::cout << "Variable value tokens:" << std::endl;
    for(ktr=variable_value_token_match.begin();ktr!=variable_value_token_match.end();ktr++)
    {
        std::cout<<ktr->first<<" "<<ktr->second<<std::endl;
    }
}

void PrintTokens(std::string token_class) {
    if(token_class == "single_char") {
        std::map<SingleCharTokenType, std::string>::iterator itr;
        for(itr=single_char_token_match.begin();itr!=single_char_token_match.end();itr++)
        {
            std::cout<<itr->first<<" "<<itr->second<<std::endl;
        }
    }
    else if(token_class == "multiple_chars") {
        std::map<MultipleCharsTokenType, std::string>::iterator itr;
        for(itr=multiple_chars_token_match.begin();itr!=multiple_chars_token_match.end();itr++)
        {
            std::cout<<itr->first<<" "<<itr->second<<std::endl;
        }
    }
    else if(token_class == "variable_value") {
        std::map<VariableValueTokenType, std::string>::iterator itr;
        for(itr=variable_value_token_match.begin();itr!=variable_value_token_match.end();itr++)
        {
            std::cout<<itr->first<<" "<<itr->second<<std::endl;
        }
    }
}

void TokenizeCode(std::string code) {
    std::vector line_chunks = split(code, ';');
    
    for(int i = 0; i < line_chunks.size(); i++) {
        std::cout << "Tokenizing line: \"" << line_chunks[i] << "\"" << std::endl;
        Token tkn = Token(line_chunks[i]);
        tkn.run();
        // tkn.print_tokens();
    }
}
