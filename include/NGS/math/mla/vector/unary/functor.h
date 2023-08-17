#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/scalar/unary/functor.h"

NGS_MLA_BEGIN

/**
 * @brief Unary functor concept
 *
 * @concept CVectorExpression
 *
 * @tparam _Expression CVectorExpression
 *
 * @property static function element_type apply(const _Expression&, size_t)
*/
template<class  T, class  _Expression>
concept CVectorUnaryFunctor = CVectorExpression<_Expression> &&
	requires(_Expression expr, const _Expression expr_cst) {
		{ T::apply(expr_cst, 0) } -> std::convertible_to<typename _Expression::element_type>;
};
template<CVectorExpression _Expression, CScalarUnaryFunctor _Functor>
	requires requires(_Expression e) {
		{ _Functor::apply(e()(0)) } -> std::convertible_to<typename _Expression::element_type>;
}struct NGS_API VectorUnaryScalarFunctor {
private:
	using expression_type = _Expression;
	using functor_type = _Functor;
public:

	constexpr static typename functor_type::result_type apply(const expression_type& expr, size_t i) {
		return functor_type::apply(expr()(i));
	}
};


NGS_MLA_END
