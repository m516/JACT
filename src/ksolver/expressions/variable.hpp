#pragma once

#include <memory>
#include <exception>
#include <stdexcept>
#include <typeinfo>

#include "expression.hpp"
#include "solver.hpp"


#define DEBUG

namespace ksolver{

class Variable : public Expression{
    const Property &property;

    Variable(const Solver &solver, const Property& ID) : Expression(solver), property(property){}

    virtual bool fixed(){return property.fixed;}

    virtual number_t evaluate() {return property.value;}

    virtual bool operator == (const Expression& other){
        //Expressions are not equal if "other" is not a variable
        if(typeid(other) != typeid(Variable)) return false;
        //Compare the addresses of the property values.
        //Forcing a cast to a Variable type because any other type would have returned false
        return &(((Variable*)&other)->property)==&property;
    }

};


}