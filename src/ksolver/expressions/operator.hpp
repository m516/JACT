#pragma once

#include <memory>
#include <exception>
#include <stdexcept>


#include "expression.hpp"

#define DEBUG

namespace ksolver{

/**
 * @brief An abstract class that represents an operator.
 * An operator is any expression that comprises one or more expressions.
 */
template<size_t N>
class Operator : public Expression{
    public:

    Operator(){
        //Assuming ownership in all child expressions. 
        //Everything is set to null
        for(size_t i = 0; i < N; i++) _operand[i] = nullptr;
    }

    /**
     * @brief Returns the i'th expression in this operator. Read only
     * 
     * @param index 
     * @return Expression 
     */
    const Expression* operator[](size_t index) const {return _operand[N];}

    virtual ~Operator(){
        //Assuming ownership in all child expressions. 
        //Delete all the child expressions
        for(size_t i = 0; i < N; i++) delete _operand[i];
    }

    /**
     * @brief Set the expression object at a given index. 
     * Creates a new deep copy of the original operand passed in the parameter,
     * and stores it locally until replaced or deleted
     * 
     * @param new_operand the new operand
     * @param index the index to place the operand
     */
    void set_expression(const Expression& new_operand, size_t index){
        #ifdef DEBUG
        if(index >= N) throw std::invalid_argument("Array index out of bounds");
        #endif

        //Delete the existing expression
        if(_operand[i]!=nullptr)
            delete _operand[i];
        //Create a deep copy of the expression
        _operand[i] = new (typeid(expression))(expression);
    }


    /**
     * @brief Returns true if this epxression does not depend on the value of a variable
     * 
     * @return true if all operands are fixed
     * @return false if any operands are not fixed
     */
    virtual bool fixed(){
        for(size_t i = 0; i < N; i++) 
            if(_operand[i] != nullptr && !_operand[i]->fixed())
                return false;

        return true;
    }

    protected:
    /**
     * @brief The list of operands
     * 
     */
    Expression* _operand[N];
};


}