
#include "operator.hpp"
#include "addition.hpp"
#include "expression.hpp"

namespace ksolver{
namespace Operators{

extern const Operator addition {
    2,

    
    [](Expression const & expr) -> number_t{
        number_t a = expr.properties.expr_operator.operand[0]->evaluate();
        number_t b = expr.properties.expr_operator.operand[1]->evaluate();
        return a+b;
    },

    [](Expression const & expr) -> Expression{
        return Expression(expr);
    },

    &subtraction

};

extern const Operator subtraction {
    2,

    
    [](Expression const & expr) -> number_t{
        number_t a = expr.properties.expr_operator.operand[0]->evaluate();
        number_t b = expr.properties.expr_operator.operand[1]->evaluate();
        return a-b;
    },

    [](Expression const & expr) -> Expression{
        return Expression(expr);
    },

    &addition

};

}}