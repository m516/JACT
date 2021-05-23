#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <vector>

#include "expression.hpp"
#include "property.hpp"
#include "operators.hpp"


#define DEBUG

namespace ksolver{

class Solver{
    public:
    std::vector<Expression> equations;
    std::vector<Property> properties;
};


}
