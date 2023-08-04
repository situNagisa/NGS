#pragma once

#include "NGS/mla/vector/binary/macro_begin.h"

NGS_MLA_BEGIN

NGS_MLA_VECTOR_BINARY_OPERATOR(+, ScalarPlusFunctor, plus);
NGS_MLA_VECTOR_BINARY_OPERATOR(-, ScalarMinusFunctor, minus);
NGS_MLA_VECTOR_BINARY_OPERATOR(*, ScalarMultipliesFunctor, multiplies);
NGS_MLA_VECTOR_BINARY_OPERATOR(/ , ScalarDividesFunctor, divides);

NGS_MLA_VECTOR_BINARY_SCALAR_OPERATOR(+, ScalarPlusFunctor, plus_scalar);
NGS_MLA_VECTOR_BINARY_SCALAR_OPERATOR(-, ScalarMinusFunctor, minus_scalar);
NGS_MLA_VECTOR_BINARY_SCALAR_OPERATOR(*, ScalarMultipliesFunctor, multiplies_scalar);
NGS_MLA_VECTOR_BINARY_SCALAR_OPERATOR(/ , ScalarDividesFunctor, divides_scalar);

NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(+);
NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(-);
NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(*);
NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(/ );

//NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(swap, ScalarSwapFunctor);

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension)
constexpr bool compare(const _Expression1& expr1, const _Expression2& expr2) {
	for (size_t i = 0; i < _Expression1::dimension; ++i) {
		if (expr1()(i) != expr2()(i))return false;
	}
	return true;
}
template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension)
constexpr bool operator==(const _Expression1& expr1, const _Expression2& expr2) {
	return compare(expr1, expr2);
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension)
constexpr mpl::promote_t<
	typename vector_traits<_Expression1>::element_type,
	typename vector_traits<_Expression2>::element_type
> product_inner(const _Expression1& expr1, const _Expression2& expr2) {
	using element_type1 = typename vector_traits<_Expression1>::element_type;
	using element_type2 = typename vector_traits<_Expression2>::element_type;
	using promote_type = mpl::promote_t<element_type1, element_type2>;
	promote_type result = 0;
	for (size_t i = 0; i < _Expression1::dimension; ++i) {
		result += expr1()(i) * expr2()(i);
	}
	return result;
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension)
constexpr auto operator%(const _Expression1& expr1, const _Expression2& expr2) {
	return product_inner(expr1, expr2);
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 3)
constexpr vector_binary_functor_trait_t<_Expression1, _Expression2, VectorBinaryProductOuterFunctor> product_outer(const _Expression1& expr1, const _Expression2& expr2) {
	return vector_binary_functor_trait_t<_Expression1, _Expression2, VectorBinaryProductOuterFunctor>(expr1, expr2);
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 2)
constexpr mpl::promote_t<
	typename vector_traits<_Expression1>::element_type,
	typename vector_traits<_Expression2>::element_type
> product_outer(const _Expression1& expr1, const _Expression2& expr2) {
	return expr1()(0) * expr2()(1) - expr1()(1) * expr2()(0);
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 3)
constexpr auto operator^(const _Expression1& expr1, const _Expression2& expr2) {
	return product_outer(expr1, expr2);
}

template<CVectorContainer _Container, CVectorExpression _Expression>
	requires (_Container::dimension == _Expression::dimension) && (_Container::dimension == 3)
constexpr auto& operator^=(_Container& container, const _Expression& expression) {
	return container.assign(product_outer(container, expression));
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 2)
constexpr auto operator^(const _Expression1& expr1, const _Expression2& expr2) {
	return product_outer(expr1, expr2);
}


NGS_MLA_END

#include "NGS/mla/vector/binary/macro_end.h"