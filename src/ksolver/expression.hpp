#pragma once

#include "property.hpp"
#include "operator.hpp"
#include "number.hpp"
#include <memory>

class Solver;

namespace ksolver{

/**
 * @brief A class that represents an expression.
 * Implemented by operators, variables, or constants
 * 
 */
class Expression{

    private:

    /**
     * @brief Fields specific to operators
     * 
     */
    struct expression_operator{
        Expression* operand[2];
        Operator operator_inst;
    };

    /**
     * @brief Fields related to variables
     * 
     */
    struct expression_variable{
        Property* property;
    };

    /**
     * @brief Fields related to constants
     * 
     */
    struct expression_constant{
        number_t value;
    };

    /**
     * @brief A union used to store all the properties related to either operators, variables, or constants
     * 
     */
    union properties_t{
        struct expression_operator expr_operator;
        struct expression_variable expr_variable;
        struct expression_constant expr_constant;
    };

    /**
     * @brief A type of expression, either operators, variables, or constants.
     * 
     */
    enum class expression_type { 
        Operator, 
        Variable, 
        Constant 
    };

    public:

    /**
     * @brief The type of the root of this expression. Must be Operator, Variable, or Constant
     * 
     */
    const expression_type type;

    /**
     * @brief The list of properties of this expression. Depends on type.
     * 
     */
    union properties_t properties;

    /**
     * @brief The solver
     * 
     */
    const Solver &solver;

    /**
     * @brief Construct a new variable based on a property
     * 
     * @param solver 
     * @param property 
     */
    Expression(const Solver &solver, Property* property) : solver(solver), type(expression_type::Variable) {
        properties.expr_variable.property = property;
    }

    /**
     * @brief Construct a new constant based on a value
     * 
     * @param solver 
     * @param value 
     */
    Expression(const Solver &solver, number_t value) : solver(solver), type(expression_type::Constant) {
        properties.expr_constant.value = value;
    }

    /**
     * @brief Construct a new operator-based expression based on an Operator type and two expressions that represent operands
     * 
     * @param solver 
     * @param op the Operator to use (i.e. an Operator instance that does addition/subtraction/multiplication/sine/etc.)
     * @param operand1 
     * @param operand2 
     */
    Expression(const Solver &solver, const Operator &op, Expression *operand1 = nullptr, Expression *operand2 = nullptr) :
    solver(solver),
    type(expression_type::Operator){
        properties.expr_operator.operator_inst = op;
        properties.expr_operator.operand[0]=operand1;
        properties.expr_operator.operand[1]=operand2;
    }    

    /**
     * @brief Evaluates the expression and returns the value
     * 
     * @return number_t the evaluated value of the expression 
     */
    virtual number_t evaluate(){
        switch(type){
            case expression_type::Constant:
            return properties.expr_constant.value;

            case expression_type::Operator:
            return properties.expr_operator.operator_inst.evaluate(*this);

            case expression_type::Variable:
            return properties.expr_variable.property->value;
        }
    }

    /**
     * @brief Returns true if this solution does not depend on the value of a variable
     * 
     * @return true this expression does not depend on the value of a variable
     * @return false this expression does depend on the value of a variable
     */
    bool fixed(){
        switch(type){
            case expression_type::Constant:
            return true;

            case expression_type::Operator:
            for(int i = 0; i < 2; i++)
                if(properties.expr_operator.operand[i] != nullptr)
                    if(!properties.expr_operator.operand[i]->fixed()) return false;
            return true;

            case expression_type::Variable:
            return properties.expr_variable.property->fixed;
        }
    }
};


}