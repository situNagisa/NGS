#pragma once

#include "NGS/mla/base/traits.h"
#include "NGS/mla/matrix/expression.h"
#include "NGS/mla/matrix/tag.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression>
struct matrix_traits : type_traits<_Expression> {
private:
	using base_type = typename matrix_traits::self_type;
private:
	using self_type = matrix_traits<_Expression>;
public:
	using original_type = typename _Expression::expression_type;
	using element_type = typename _Expression::element_type;
	using closure_type = std::conditional_t<std::derived_from<typename original_type::type_category, tag::matrix_container>, const original_type&, const original_type>;
	constexpr static size_t row_size = original_type::row_size;
	constexpr static size_t col_size = original_type::col_size;
	constexpr static bool is_container = std::derived_from<typename original_type::type_category, tag::matrix_container>;
};

template<CMatrixExpression _Expression1, CMatrixExpression _Expression2>
constexpr bool is_similar = matrix_traits<_Expression1>::row_size == matrix_traits<_Expression2>::row_size && matrix_traits<_Expression1>::col_size == matrix_traits<_Expression2>::col_size;

template<CMatrixExpression _Expression>
	requires (matrix_traits<_Expression>::is_container)
constexpr bool is_row_major = std::derived_from<typename matrix_traits<_Expression>::original_type::major_category, tag::row>;

template<CMatrixExpression _Expression>
	requires (matrix_traits<_Expression>::is_container)
constexpr bool is_col_major = std::derived_from<typename matrix_traits<_Expression>::original_type::major_category, tag::column>;

NGS_MLA_END
