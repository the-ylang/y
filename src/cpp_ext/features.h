#ifndef __FEATURES_H__
#define __FEATURES_H__

/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Features
*/

#include <iostream>
#include <string>
#include <vector>

bool in(std::vector<std::string> list, std::string value) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

#endif // __FEATURES_H__