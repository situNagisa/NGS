#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/scalar/unary/functor.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN

/**
 * @brief Unary functor concept
 *
 * @concept CMatrixUnaryFunctor
 *
 * @tparam _Expression CMatrixExpression
 *
 * @property static function element_type apply(const _Expression&, size_t)
*/
template<class  T, class  _Expression>
concept CMatrixUnaryFunctor = CMatrixExpression<_Expression> && requires(_Expression expr, const _Expression expr_cst, size_t index, size_t row_index, size_t col_index) {
	{ T::apply(expr_cst, row_index, col_index) } -> std::convertible_to<typename _Expression::element_type>;
};


template<CMatrixExpression _Expression, CScalarUnaryFunctor _Functor>
	requires requires(typename _Expression::element_type element) {
		{ _Functor::apply(element) } -> std::convertible_to<typename _Expression::element_type>;
}struct NGS_DLL_API MatrixUnaryScalarFunctor {
private:
	using expression_type = _Expression;
	using functor_type = _Functor;
public:
	constexpr static typename functor_type::result_type apply(const expression_type& expr, size_t row_index, size_t col_index) {
		return functor_type::apply(expr()(row_index, col_index));
	}
};

NGS_MLA_END
