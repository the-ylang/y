#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

// split with string
std::vector<std::string> split(std::string string_to_split, std::string delimiter) {
    std::vector<std::string> splitted_string;
    int index = 0;
    int delimiter_index = 0;
    while (true) {
        delimiter_index = string_to_split.find(delimiter, index);
        if (delimiter_index == std::string::npos) {
            splitted_string.push_back(string_to_split.substr(index, string_to_split.size() - index));
            break;
        }
        else {
            splitted_string.push_back(string_to_split.substr(index, delimiter_index - index));
            index = delimiter_index + delimiter.size();
        }
    }
    std::string* final_string = &splitted_string[0];
    return splitted_string;
}

// split with char
std::vector<std::string> split(std::string string_to_split, char delimiter) {
    std::vector<std::string> splitted_string;
    std::string temp = "";
    for(int i = 0; i < string_to_split.length(); i++) {
        if(string_to_split[i] == delimiter) {
            splitted_string.push_back(temp);
            temp = "";
        } else {
            temp += string_to_split[i];
        }
    }
    splitted_string.push_back(temp);
    while(splitted_string[splitted_string.size() - 1] == "") {
        splitted_string.pop_back();
    }
    splitted_string = RemoveValue(splitted_string, std::string(1, delimiter));
    return splitted_string;
}

// in (string)
bool in(std::string substring_to_check, std::string string_to_check_in) {
    return string_to_check_in.find(substring_to_check) != std::string::npos;
}

// in (char)
bool in(char char_to_check, std::string string_to_check_in) {
    return string_to_check_in.find(char_to_check) != std::string::npos;
}

// RemoveValue
std::vector<std::string> RemoveValue(std::vector<std::string> vector_to_remove_from, std::string value_to_remove) {
    std::vector<std::string> vector_removed;
    for(int i = 0; i < vector_to_remove_from.size(); i++) {
        if(vector_to_remove_from[i] != value_to_remove && vector_to_remove_from[i] != "") {
            vector_removed.push_back(vector_to_remove_from[i]);
        }
    }
    return vector_removed;
}

// Check number
bool isNumber(std::string string_to_check) {
    for(char act : string_to_check) {
        if(!in(act, "0123456789")) {
            return false;
        }
    }
    return true;
}

// Check word
bool isWord(std::string string_to_check) {
    for(char act : string_to_check) {
        if(!in(act, "abcdefghijklmnopqrstuvwxyzABCDEFGHIKJLMNOPQRSTUVWXYZ_")) {
            return false;
        }
    }
    return true;
}