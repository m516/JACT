#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <typeinfo>

#include "expression.hpp"
#include "solver.hpp"


#define DEBUG

namespace ksolver{

class Constant : public Expression{
    public:

    number_t value;

    Constant(const Solver &solver, number_t value = 0) : Expression(solver), value(value) {}

    virtual bool fixed(){return true;}

    virtual number_t evaluate() {return value;}

};


}