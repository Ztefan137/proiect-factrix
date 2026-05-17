//
// Created by stefa on 5/17/2026.
//

#include "../../include/ui_negative_dimension_exception.h"

[[maybe_unused]]
const char *ui_negative_dimension_exception::what() const noexcept {
    return "error:negative dimension for ui";
}