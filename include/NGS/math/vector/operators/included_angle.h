#pragma once

#include "../expression.h"
#include "./product.h"
#include "./norm.h"

NGS_MATH_VECTOR_BEGIN

namespace detail {
	/**
	 * \brief 角度を求めることができるか
	 *
	 * \tparam _L 左辺の型, expressionを継承している必要がある
	 * \tparam _R 右辺の型, expressionを継承している必要がある
	 */
	template<class _L, class _R>
	concept included_angleable = []
	{
		using left_value_type = functor::vector_value_t<_L>;
		using right_value_type = functor::vector_value_t<_R>;

		if constexpr (!functor::normable<left_value_type, right_value_type>)
			return false;
		else
		{
			using left_norm_type = decltype(norm(declval<_L>(), declval<_R>()));
			using right_norm_type = decltype(norm(declval<_R>(), declval<_L>()));

			if constexpr (!cpt::multipliable<left_norm_type, right_norm_type>)
				return false;
			else
			{
				using norm_square_type = type_traits::multiply_t<left_norm_type, right_norm_type>;
				using inner_type = decltype(product_inner(declval<_L>(), declval<_R>()));

				if constexpr (!cpt::divisible<inner_type, norm_square_type>)
					return false;
				else
				{
					using divide_type = type_traits::divide_t<inner_type, norm_square_type>;

					return requires{ std::acos(declval<divide_type>()); };
				}
			}
		}
	}();
}

/**
 * \brief 获取两向量的夹角
 *
 * \param left 左向量表达式
 * \param right 右向量表达式
 *
 * \return |left · right| / (|left| * |right|)
 */
constexpr auto included_angle(functor::expression auto&& left, functor::expression auto&& right)
	requires detail::included_angleable<decltype(left), decltype(right)>
{
	return std::acos(product_inner(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)) / (norm(NGS_PERFECT_FORWARD(left)) * norm(NGS_PERFECT_FORWARD(right))));
}

NGS_MATH_VECTOR_END