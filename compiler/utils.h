#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <vector>

// Splits a string into a vector of strings with a defined string delimiter
std::vector<std::string> split(std::string string_to_split, std::string delimiter);
// Splits a string into a vector of strings with a defined char delimiter
std::vector<std::string> split(std::string string_to_split, char delimiter);
// Checks if a substring is in a string
bool in(std::string substring_to_check, std::string string_to_check_in);
// Checks if a char is in a string
bool in(char char_to_check, std::string string_to_check_in);
// Removes a given string from a vector of strings
std::vector<std::string> RemoveValue(std::vector<std::string> vector_to_remove_from, std::string value_to_remove);
// Checks if a string is a valid number
bool isNumber(std::string string_to_check);
// Checks if a string is a valid word
bool isWord(std::string string_to_check);

#endif // __UTILS_H__