#pragma once

#include <memory>

class Solver;

namespace ksolver{

/**
 * @brief The data type used in calculations
 * 
 */
typedef double number_t;

/**
 * @brief An abstract class that represents an expression.
 * Implemented by operators, variables, or constants
 * 
 */
class Expression{
    public:

    

    const Solver &solver;

    Expression(const Solver &solver) : solver(solver) {}

    /**
     * @brief Evaluates the expression and returns the value
     * 
     * @return number_t the evaluated value of the expression 
     */
    virtual number_t evaluate() = 0;

    /**
     * @brief Returns true if this solution does not depend on the value of a variable
     * 
     * @return true this expression does not depend on the value of a variable
     * @return false this expression does depend on the value of a variable
     */
    virtual bool fixed() = 0;
    
    virtual ~Expression() = 0;

    protected:
};


}