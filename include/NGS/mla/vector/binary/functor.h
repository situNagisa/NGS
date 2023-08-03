#pragma once

#include "NGS/mla/vector/expression.h"
#include "NGS/mla/scalar/binary/functor.h"

NGS_MLA_BEGIN

/**
 * @brief Unary functor concept
 *
 * @concept CVectorExpression
 *
 * @tparam _Expression1 CVectorExpression
 * @tparam _Expression2 CVectorExpression
 *
 * @property static function element_type apply(const _Expression&, size_t)
*/
template<class T, class _Expression1, class _Expression2>
concept CVectorBinaryFunctor = CVectorExpression<_Expression1> && CVectorExpression<_Expression2> &&
	requires(_Expression1 expr1, const _Expression1 expr1_cst, _Expression2 expr2, const _Expression2 & expr2_cst) {
		{ T::apply(expr1_cst, expr2_cst, 0) } -> std::convertible_to<mpl::promote_t<typename _Expression1::element_type, typename _Expression2::element_type>>;
};

template<CVectorExpression _Expression1, CVectorExpression _Expression2, CScalarBinaryFunctor _Functor>
	requires requires(_Expression1 e1, _Expression2 e2) {
		{ _Functor::apply(e1()(0), e2()(0)) } -> std::convertible_to< mpl::promote_t<typename _Expression1::element_type, typename _Expression2::element_type>>;
}struct VectorBinaryScalarFunctor {
private:
	using expression_type1 = _Expression1;
	using expression_type2 = _Expression2;
	using functor_type = _Functor;
public:

	constexpr static typename functor_type::result_type apply(const expression_type1& expr1, const expression_type2& expr2, size_t i) {
		return functor_type::apply(expr1()(i), expr2()(i));
	}
};


NGS_MLA_END
