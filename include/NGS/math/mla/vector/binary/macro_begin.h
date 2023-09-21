#include "NGS/math/mla/vector/binary/traits.h"
#include "NGS/math/mla/scalar/binary/operator.h"
#include "NGS/math/mla/vector/expression/scalar.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/traits.h"

#define NGS_MLA_VECTOR_BINARY_OPERATOR(op,functor,function_name)                    \
template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires CVectorSameDimension<_Expression1,_Expression2> \
constexpr auto function_name(const _Expression1& expr1, const _Expression2& expr2) {\
    return vector_binary_scalar_traits_t<_Expression1, _Expression2, functor>(expr1, expr2);\
}\
template<CVectorContainer _Container, CVectorExpression _Expression> requires (_Container::dimension == _Expression::dimension)\
constexpr _Container& function_name##_assign(_Container& container, const _Expression& expression) {\
    return container.assign(function_name(container, expression));\
}\
template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires CVectorSameDimension<_Expression1,_Expression2> \
constexpr auto operator op(const _Expression1& expr1, const _Expression2& expr2) { return function_name(expr1, expr2); };\
template<CVectorContainer _Container, CVectorExpression _Expression> requires (_Container::dimension == _Expression::dimension)\
_Container& operator op##=(_Container& container, const _Expression& expression) { return function_name##_assign(container,expression); };\
template<CVectorExpression _Expression, CScalarExpression _ElementType> \
constexpr auto function_name##_scalar(const _Expression& expression, _ElementType scalar) {\
    using scalar_expr = vector_scalar_expression_t<_Expression::dimension, _ElementType>; \
    return vector_binary_scalar_traits_t<_Expression, scalar_expr, functor>(expression, scalar_expr(scalar));\
} \
template<CVectorExpression _Expression, CScalarExpression _ElementType> \
constexpr auto function_name##_scalar(_ElementType scalar, const _Expression& expression) {\
    using scalar_expr = vector_scalar_expression_t<_Expression::dimension, _ElementType>; \
    return vector_binary_scalar_traits_t<scalar_expr, _Expression, functor>(scalar_expr(scalar), expression);\
} \
template<CVectorContainer _Container, CScalarExpression _ElementType>\
constexpr _Container& function_name##_assign(_Container& container, _ElementType scalar) {\
    return container.assign(function_name##_scalar(container, scalar));\
}\
template<CVectorExpression _Expression, CScalarExpression _ElementType> \
constexpr auto operator op(const _Expression& expression, _ElementType scalar) { return function_name##_scalar(expression, scalar); }\
template<CVectorExpression _Expression, CScalarExpression _ElementType> \
constexpr auto operator op(_ElementType scalar, const _Expression& expression) { return function_name##_scalar(scalar, expression); }\
template<CVectorContainer _Container, CScalarExpression _ElementType>\
constexpr _Container& operator op##=(_Container& container, _ElementType scalar) {\
    return container.assign(function_name##_scalar(container, scalar));\
}\
//