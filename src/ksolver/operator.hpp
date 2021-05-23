#pragma once

#include "number.hpp"


namespace ksolver{


class Expression;


/**
 * @brief A struct that represents an operator
 * 
 */
typedef struct operator_t{

    size_t num_params = 0;

    number_t  (*evaluate)(Expression const &) = nullptr;

    Expression (*simplify)(Expression const &) = nullptr;

    const struct operator_t* inverse = nullptr;

} Operator;

}