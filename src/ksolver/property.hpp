#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <string>

#include "expression.hpp"
#include "number.hpp"


#define DEBUG

namespace ksolver{

class Property{
    public:
    number_t value = 0;
    bool fixed = false;
    std::string name;
};


}