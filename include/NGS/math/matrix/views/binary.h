#pragma once

#include "../concept.h"
#include "../operate.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept multipiable = input_matrix<_L> && input_matrix<_R> && vectors::maybe_same_extent<::std::ranges::range_value_t<_L>, _R>;

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t minor, index_t major, auto&& left, auto&& right)const
		{
			return vectors::ops::product_inner(NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::major(left, major), NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::minor(right, minor));
		}
	}multiply_transformer{};

	template<extent_t _Extent>
	struct multiply_minor_sentinel_t
	{
		constexpr decltype(auto) operator()(auto&& left, auto&& right)const
		{
			return NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<_Extent>()(NGS_PP_PERFECT_FORWARD(right), NGS_PP_PERFECT_FORWARD(left));
		}
	};
	template<extent_t _Extent>
	inline constexpr multiply_minor_sentinel_t<_Extent> multiply_minor_sentinel{};

	template<class _L, class _R> requires multipiable<_L, _R>
	using multiply_view = transform_view<
		multiply_transformer,
		major_static_extent_v<_L, _R>, minor_static_extent_v<_R, _L>,
		NGS_MATH_MATRIX_OPERATE_NS::default_major_sentinel<major_static_extent_v<_L, _R>>(),
		multiply_minor_sentinel<minor_static_extent_v<_R, _L>>,
		//functional::binders::bind(
		//	NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<minor_extent_v<_R>>(),
		//	functional::parameter_packet::placeholders::_2,
		//	functional::parameter_packet::placeholders::_1),
		_L, _R>;
}

using _detail::multiply_view;
using vectors::views::add_view;
using vectors::views::subtract_view;

using vectors::views::add;
using vectors::views::subtract;

template<class _L, class _R> requires _detail::multipiable<_L, _R>
constexpr auto multiply(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(vectors::ops::access(NGS_PP_PERFECT_FORWARD(left), 0), right);
	return multiply_view<_L&&, _R&&>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_MODULE_END

NGS_LIB_BEGIN

template<operator_matrix _L, operator_matrix _R> requires maybe_same_type<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_matrix _L, operator_matrix _R> requires maybe_same_type<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_matrix _L, operator_matrix _R> requires NGS_LIB_MODULE_NAME::_detail::multipiable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END