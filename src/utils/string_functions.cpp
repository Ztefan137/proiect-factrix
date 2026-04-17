//
// Created by stefa on 4/11/2026.
//
#include <vector>
#include <algorithm>
#include <string>
#include "string_functions.h"
std::vector<std::string> st::split(const std::string& s, char delim) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t pos;

    while ((pos = s.find(delim, start)) != std::string::npos) {
        result.emplace_back(s.substr(start, pos - start));
        start = pos + 1;
    }

    result.emplace_back(s.substr(start));
    return result;
}

std::string st::trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}
