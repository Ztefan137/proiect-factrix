//
// Created by stefa on 5/17/2026.
//

#ifndef OOP_UI_EXCEPTION_H
#define OOP_UI_EXCEPTION_H
#include <exception>


class ui_exception : public std::exception {
public:
    const char *what() const noexcept override;
};


#endif //OOP_UI_EXCEPTION_H