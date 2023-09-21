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
NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CMatrixExpression,is_matrix_expression,
	CExpression,
	requires(_Type matrix, const _Type matrix_cst, size_t row_index, size_t col_index) {
	typename _Type::element_type;
	{ _Type::row_count } -> std::convertible_to<size_t>;
	{ _Type::col_count } -> std::convertible_to<size_t>;
	{ _Type::element_count } -> std::convertible_to<size_t>;

	{ matrix_cst(row_index, col_index) } -> std::convertible_to<typename _Type::element_type>;

	//{ matrix_cst().row(row_index) };
	//{ matrix_cst().column(col_index) };

		requires std::derived_from<typename _Type::type_category, tag::matrix>;
});

NGS_MLA_END
