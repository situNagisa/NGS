#pragma once

#include "NGS/mla/base/expression.h"
#include "NGS/mla/matrix/tag.h"

NGS_MLA_BEGIN

/**
 * @brief Matrix expression concept.
 *
 * @concept derived_from CExpression
 *
 * @property static size_t row_size
 * @property static size_t col_size
 * @property type element_type
 * @property element_type operator()(size_t);
 * @property element_type operator()(size_t)const;
 * @property element_type operator()(size_t, size_t);
 * @property element_type operator()(size_t, size_t)const;
*/
template<class _Expression = void>
concept CMatrixExpression = CExpression<_Expression> && requires(_Expression matrix, const _Expression matrix_cst) {
	typename _Expression::element_type;
	{ _Expression::row_size } -> std::convertible_to<size_t>;
	{ _Expression::col_size } -> std::convertible_to<size_t>;

	{ matrix(0) } -> std::convertible_to<typename _Expression::element_type>;
	{ matrix_cst(0) } -> std::convertible_to<typename _Expression::element_type>;

	{ matrix(0, 0) } -> std::convertible_to<typename _Expression::element_type>;
	{ matrix_cst(0, 0) } -> std::convertible_to<typename _Expression::element_type>;

		requires std::derived_from<typename _Expression::type_category, tag::matrix>;
};

template<ccpt::CRPT<CMatrixExpression<>> _Expression>
struct MatrixExpression : Expression<_Expression> {
private:
	using base_type = MatrixExpression::self_type;
protected:
	using self_type = MatrixExpression<_Expression>;
public:
	using type_category = tag::matrix;
	constexpr size_t row_size = 0;
	constexpr size_t col_size = 0;
};

NGS_MLA_END
