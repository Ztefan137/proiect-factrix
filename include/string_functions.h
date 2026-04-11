//
// Created by stefa on 4/11/2026.
//

#ifndef OOP_STRING_FUNCTIONS_H
#define OOP_STRING_FUNCTIONS_H

#include <string>
#include <vector>

namespace st{
    std::vector<std::string> split(const std::string& s, char delim);
    std::string trim(const std::string& s);
}
#endif //OOP_STRING_FUNCTIONS_H