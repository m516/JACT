#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <vector>

#include "expression.hpp"
#include "property.hpp"


#define DEBUG

namespace ksolver{

class Solver{
    public:
    std::vector<Expression*> expressions;
    std::vector<Property> properties;
};


}