//
// Created by stefa on 5/17/2026.
//

#ifndef OOP_UI_NEGATIVE_DIMENSION_EXCEPTION_H
#define OOP_UI_NEGATIVE_DIMENSION_EXCEPTION_H
#include "ui_exception.h"


class ui_negative_dimension_exception : public ui_exception {
public:
    const char *what() const noexcept;
};


#endif //OOP_UI_NEGATIVE_DIMENSION_EXCEPTION_H