#pragma once

#include "NGS/math/mla/base/expression.h"
#include "NGS/math/mla/vector/tag.h"
#include "NGS/math/mla/iterator_interface.h"


NGS_MLA_BEGIN

/**
 * @brief Vector expression concept
 *
 * @concept CExpression
 *
 * @property static size_t dimension
 * @property type element_type
 * @property function element_type operator()(size_t)const;
*/
NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CVectorExpression, is_vector_expression,
	CExpression,
	requires(_Type expr, const _Type expr_cst) {
	typename _Type::element_type;
	{ _Type::dimension } -> std::convertible_to<size_t>;
	{ expr_cst(0) } -> std::convertible_to<typename _Type::element_type>;
		requires std::derived_from<typename _Type::type_category, tag::vector>;
});

template<CVectorExpression _Type1, CVectorExpression _Type2>
inline constexpr bool _is_vector_same_dimension = _Type1::dimension == _Type2::dimension;

template<class _Type1,class _Type2>
concept CVectorSameDimension = _is_vector_same_dimension<std::remove_cvref_t<_Type1>, std::remove_cvref_t<_Type2>>;

template<CVectorExpression _Vector,ccpt::UInt _Dimension>
inline constexpr bool _is_vector_dimension_equal = _Vector::dimension == _Dimension::value;

template<class _Vector,size_t _Dimension>
concept CVectorDimensionEqual = _is_vector_dimension_equal<std::remove_cvref_t<_Vector>, ccpt::uint_<_Dimension>>;

NGS_MLA_END
