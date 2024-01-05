#pragma once

#include "./product.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

/**
 *	\brief 是否可求范数
 *	\note 这里的\code cpt::real_number \endcode 待议，因为不一定只有实数才能开方
*/
template<class _T>
concept normable = inner_productable<_T, _T>&& cpt::real_number<traits::vectors::inner_product_t<_T, _T>>;

NGS_MATH_LA_VECTOR_CONCEPT_END
NGS_MATH_LA_VECTOR_TRAIT_BEGIN

template<class _T> requires concepts::vectors::normable<_T>
using norm_t = type_traits::naked_t<type_traits::add_t<type_traits::multiply_t<value_t<_T>, value_t<_T>>>>;

NGS_MATH_LA_VECTOR_TRAIT_END
NGS_MATH_LA_VECTOR_RANGE_BEGIN

constexpr auto norm_squared(concepts::vectors::inner_productable auto&& expr) { return vectors::product_inner(expr, expr); }

constexpr auto norm(concepts::vectors::normable auto&& expr) { return basic::sqrt(vectors::norm_squared(NGS_PP_PERFECT_FORWARD(expr))); }

NGS_MATH_LA_VECTOR_RANGE_END