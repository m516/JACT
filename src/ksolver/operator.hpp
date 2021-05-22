#pragma once

#include "number.hpp"


namespace ksolver{


class Expression;


/**
 * @brief A class that represents an operator
 * 
 */
struct Operator{

    size_t num_params;

    number_t (*evaluate)(Expression const &);

    Expression (*simplify)(Expression &);

    Operator* inverse;

};

}