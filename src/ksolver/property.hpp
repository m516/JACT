#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <string>

#include "expression.hpp"


#define DEBUG

namespace ksolver{

class Property{
    public:
    number_t value;
    bool fixed;
    std::string name;
};


}