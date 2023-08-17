#pragma once

#include "NGS/math/mla/base/traits.h"
#include "NGS/math/mla/matrix/tag.h"
#include "NGS/math/mla/matrix/expression/concept.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression>
struct NGS_API matrix_traits : type_traits<_Expression> {
private:
	using base_type = typename matrix_traits::self_type;
private:
	using self_type = matrix_traits<_Expression>;
public:
	using original_type = typename _Expression::expression_type;
	using element_type = typename _Expression::element_type;
	using closure_type = std::conditional_t<
		std::derived_from<typename original_type::type_category, tag::matrix_container> && !std::is_rvalue_reference_v<_Expression>,
		const original_type&,
		const original_type>;

	constexpr static size_t complexity = original_type::complexity;
	constexpr static size_t row_count = original_type::row_count;
	constexpr static size_t col_count = original_type::col_count;
	constexpr static bool is_container = std::derived_from<typename original_type::type_category, tag::matrix_container>;
};

template<CMatrixExpression _Expression1, CMatrixExpression _Expression2>
constexpr bool is_similar = matrix_traits<_Expression1>::row_count == matrix_traits<_Expression2>::row_count && matrix_traits<_Expression1>::col_count == matrix_traits<_Expression2>::col_count;

template<class > constexpr bool is_row_major = false;
template<std::derived_from<tag::row> _Layout> constexpr bool is_row_major<_Layout> = true;
template<CMatrixExpression _Expression> requires (matrix_traits<_Expression>::is_container)
constexpr bool is_row_major<_Expression> = is_row_major<typename matrix_traits<_Expression>::original_type::layout_category>;

template<class > constexpr bool is_col_major = false;
template<std::derived_from<tag::column> _Layout> constexpr bool is_col_major<_Layout> = true;
template<CMatrixExpression _Expression> requires (matrix_traits<_Expression>::is_container)
constexpr bool is_col_major<_Expression> = is_col_major<typename matrix_traits<_Expression>::original_type::layout_category>;

template<CMatrixExpression _Expression>
constexpr bool is_square_matrix = matrix_traits<_Expression>::col_count == matrix_traits<_Expression>::row_count;

NGS_MLA_END
