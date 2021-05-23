#pragma once

#include "property.hpp"
#include "operator.hpp"
#include "number.hpp"
#include <memory>


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
        const Operator *operator_inst;
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
     * @brief Construct a new variable based on a property
     * 
     * @param solver 
     * @param property 
     */
    Expression(Property &property) : type(expression_type::Variable) {
        properties.expr_variable.property = &property;
    }

    /**
     * @brief Construct a new constant based on a value
     * 
     * @param solver 
     * @param value 
     */
    Expression(number_t value) : type(expression_type::Constant) {
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
    Expression(const Operator &op, const Expression *operand1 = nullptr, const Expression *operand2 = nullptr) :
    type(expression_type::Operator){
        properties.expr_operator.operator_inst = &op;
        if (operand1 != nullptr)
            properties.expr_operator.operand[0] = new Expression(*operand1);
        if (operand2 != nullptr)
            properties.expr_operator.operand[1] = new Expression(*operand2);
    }  

    /**
     * @brief The copy constructor, makes a deep copy of this expression
     * 
     * @param expression 
     */
    Expression(const Expression &expression) : 
    type(expression.type),
    properties(expression.properties)
    {
        if(type==expression_type::Operator){
            if(expression.properties.expr_operator.operand[0] != nullptr)
                properties.expr_operator.operand[0] = new Expression(*expression.properties.expr_operator.operand[0]);
            if(expression.properties.expr_operator.operand[1] != nullptr)
                properties.expr_operator.operand[1] = new Expression(*expression.properties.expr_operator.operand[1]);
        }
    }

    /**
     * @brief Destroy the Expression object
     * 
     */
    ~Expression(){
        if(type==expression_type::Operator){
            if(properties.expr_operator.operand[0] != nullptr)
                delete properties.expr_operator.operand[0];
            if(properties.expr_operator.operand[1] != nullptr)
                delete properties.expr_operator.operand[1];
        }
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
            return properties.expr_operator.operator_inst->evaluate(*this);

            case expression_type::Variable:
            return properties.expr_variable.property->value;

            default:
            return NAN;
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
        
        //There should be no other expression types. Return false.
        return false;
    }
};


}