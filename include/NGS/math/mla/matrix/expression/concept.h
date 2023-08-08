#pragma once

#include "NGS/math/mla/base/expression.h"
#include "NGS/math/mla/matrix/tag.h"

NGS_MLA_BEGIN

/**
 * @brief Matrix expression concept.
 *
 * @concept derived_from CExpression
 * @concept CVectorExpression
 *
 * @property static size_t row_count
 * @property static size_t col_count
 * @property static size_t element_count
 * @property type element_type
 * @property type type_category *
 * @property element_type operator()(size_t, size_t)const;
 * @property CVectorExpression row(size_t); *
 * @property CVectorExpression column(size_t); *
*/
template<class _Expression = void>
concept CMatrixExpression = CExpression<_Expression> && requires(_Expression matrix, const _Expression matrix_cst, size_t row_index, size_t col_index) {
	typename _Expression::element_type;
	{ _Expression::row_count } -> std::convertible_to<size_t>;
	{ _Expression::col_count } -> std::convertible_to<size_t>;
	{ _Expression::element_count } -> std::convertible_to<size_t>;

	{ matrix_cst(row_index, col_index) } -> std::convertible_to<typename _Expression::element_type>;

	//{ matrix_cst().row(row_index) };
	//{ matrix_cst().column(col_index) };

		requires std::derived_from<typename _Expression::type_category, tag::matrix>;
};

NGS_MLA_END
