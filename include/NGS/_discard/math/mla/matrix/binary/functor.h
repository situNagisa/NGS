#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/scalar/binary/functor.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN

/**
 * @brief Unary functor concept
 *
 * @concept CMatrixExpression
 *
 * @tparam _Expression1 CMatrixExpression
 * @tparam _Expression2 CMatrixExpression
 *
 * @property static function element_type apply(const _Expression&, size_t)
*/
template<class  T, class  _Expression1, class  _Expression2>
concept CMatrixBinaryFunctor = CMatrixExpression<_Expression1> && CMatrixExpression<_Expression2> &&
	requires(_Expression1 expr1, const _Expression1 expr1_cst, _Expression2 expr2, const _Expression2 & expr2_cst, size_t row_index, size_t col_index) {
		{ T::apply(expr1_cst, expr2_cst, row_index, col_index) } -> std::convertible_to<mpl::promote_t<typename _Expression1::element_type, typename _Expression2::element_type>>;
};

template<CMatrixExpression _Expression1, CMatrixExpression _Expression2, CScalarBinaryFunctor _Functor>
	requires requires(typename matrix_traits<_Expression1>::element_type e1, typename matrix_traits<_Expression2>::element_type e2) {
		{ _Functor::apply(e1, e2) } -> std::convertible_to< mpl::promote_t<typename _Expression1::element_type, typename _Expression2::element_type>>;
}struct NGS_DLL_API MatrixBinaryScalarFunctor {
private:
	using expression_type1 = _Expression1;
	using expression_type2 = _Expression2;
	using functor_type = _Functor;
public:

	constexpr static typename functor_type::result_type apply(const expression_type1& expr1, const expression_type2& expr2, size_t row_index, size_t col_index) {
		return functor_type::apply(expr1()(row_index, col_index), expr2()(row_index, col_index));
	}
};


NGS_MLA_END
