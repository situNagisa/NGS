#pragma once

#include "NGS/mla/vector/expression/expression.h"
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

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
struct VectorBinaryProductOuterFunctor {
private:
	using expression_closure_type1 = typename vector_traits<_Expression1>::closure_type;
	using expression_closure_type2 = typename vector_traits<_Expression2>::closure_type;
	using result_type = mpl::promote_t<
		typename vector_traits<_Expression1>::element_type,
		typename vector_traits<_Expression2>::element_type
	>;
public:
	static_assert(vector_traits<_Expression1>::dimension == vector_traits<_Expression2>::dimension && vector_traits<_Expression1>::dimension == 3, "the expression's dimension should be same with 3");

	constexpr static result_type apply(expression_closure_type1 expr1, expression_closure_type2 expr2, size_t i) {
		switch (i)
		{
		case 0:
			return expr1()(1) * expr2()(2) - expr1()(2) * expr2()(1);
		case 1:
			return expr1()(2) * expr2()(0) - expr1()(0) * expr2()(2);
		case 2:
			return expr1()(0) * expr2()(1) - expr1()(1) * expr2()(0);
		}
		return {};
	}
};


NGS_MLA_END
