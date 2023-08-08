#pragma once

#include "NGS/mla/vector/expression/concept.h"
#include "NGS/mla/vector/traits.h"
#include "NGS/mla/vector/binary/binary.h"
#include "NGS/mla/vector/binary/functor.h"
#include "NGS/mla/vector/binary/traits.h"

NGS_MLA_BEGIN

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
constexpr auto operator%(const _Expression1& expr1, const _Expression2& expr2) { return product_inner(expr1, expr2); }

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
	requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 3)
constexpr auto product_outer(const _Expression1& expr1, const _Expression2& expr2) {
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

template<CVectorContainer _Container, CVectorExpression _Expression> requires (_Container::dimension == _Expression::dimension) && (_Container::dimension == 3)
constexpr _Container& product_outer_assign(_Container& container, const _Expression& expression) {
	return container.assign(product_outer(container, expression));
}

template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 3)
constexpr auto operator^(const _Expression1& expr1, const _Expression2& expr2) { return product_outer(expr1, expr2); }
template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires (_Expression1::dimension == _Expression2::dimension) && (_Expression1::dimension == 2)
constexpr auto operator^(const _Expression1& expr1, const _Expression2& expr2) { return product_outer(expr1, expr2); }

template<CVectorContainer _Container, CVectorExpression _Expression> requires (_Container::dimension == _Expression::dimension) && (_Container::dimension == 3)
constexpr _Container& operator^=(_Container& container, const _Expression& expression) { return product_outer_assign(container, expression); }



NGS_MLA_END
