#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Pars {

    class Parser {
    public:
        Parser(std::vector<std::pair<std::string, int>> tokens_to_parse, std::vector<std::string> keywords_vec) {
            tokens = tokens_to_parse;
            keywords = keywords_vec;
        }
        void Run() {
            std::cout << isDeclaration();
        }
        int GetKeywordType(std::string keyword) {
            int key_index = -1;
            for (int i = 0; i < keywords.size(); i++) {
                if (keyword == keywords[i])
                    key_index = i;
            }
            if(key_index == -1)
                return -1;
            int ret = (key_index <= 8) ? 0 :  (key_index <= 17) ? 1 : (key_index <= 21) ? 2 : (key_index <= 25) ? 3 : (key_index <= 31) ? 4 : (key_index <= 39) ? 5 : (key_index <= 46) ? 6 : (key_index <= 50) ? 7 : (key_index <= 53) ? 8 : 9;
            return ret;
        }
    private:
        std::vector<std::pair<std::string, int>> tokens;
        std::vector<std::string> keywords;
        bool isDeclaration() {
            if(
                ( // Case protected/private/public
                    ( // Protected/private/public
                        tokens[0].first == keywords[42]
                        ||
                        tokens[0].first == keywords[43]
                        ||
                        tokens[0].first == keywords[44]
                    )
                    &&
                    (
                        ( // Case const
                            tokens[1].first == keywords[6]
                            &&
                            tokens[2].first != keywords[6]
                            &&
                            GetKeywordType(tokens[2].first) == 0
                        )
                        ||
                        ( // Case not const
                            GetKeywordType(tokens[1].first) == 0
                            &&
                            tokens[1].first != keywords[6]
                        )
                    )
                )
                ||
                ( // Case not protected/private/public
                    ( // Protected/private/public
                        tokens[0].first != keywords[42]
                        &&
                        tokens[0].first != keywords[43]
                        &&
                        tokens[0].first != keywords[44]
                    )
                    &&
                    (
                        ( // Case const
                            tokens[0].first == keywords[6]
                            &&
                            tokens[1].first != keywords[6]
                            &&
                            GetKeywordType(tokens[1].first) == 0
                        )
                        ||
                        ( // Case not const
                            GetKeywordType(tokens[0].first) == 0
                            &&
                            tokens[0].first != keywords[6]
                        )
                    )
                )
            ) {
                return true;
            }
            else {
                return false;
            }
        }
    };
}

int main() {
    std::vector<std::string> keywords = {
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
    };
    std::vector<std::pair<std::string, int>> tokens_to_parse = {
        {"const", 3},
        {"x", 1},
        {"<<", 3},
        {"1", 0},
        {";", 1}
    };
    Pars::Parser parser(tokens_to_parse, keywords);
    parser.Run();
}