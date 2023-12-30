#pragma once

#include "../concept.h"
#include "../tag.h"
#include "../access.h"
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
			return vectors::product_inner(NGS_LIB_NAME::major(left, major), NGS_LIB_NAME::minor(right, minor));
		}
	}multiply_transformer{};

	template<class _L, class _R> requires multipiable<_L, _R>
	using multiply_view = transform_view<
		major_static_extent<_L, _R>, minor_static_extent<_R, _L>,
		multiply_transformer,
		default_major_sizer<major_extent_v<_L>>(),
		default_minor_sizer<minor_extent_v<_R>>(),
		//statics::functional::bind(default_minor_sizer<minor_extent_v<_R>>(), statics::functional::placeholders::_2, statics::functional::placeholders::_1),
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
	return multiply_view<_L&&, _R&&>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_MODULE_END

NGS_LIB_BEGIN

namespace detail
{
	template<class _L, class _R>
	concept allow_operator_functor =
		tag_matrix<_L> && tag_matrix<_R> &&
		scalar_matrix<_L> && scalar_matrix<_R>;
}

template<class _L, class _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires detail::allow_operator_functor<_L, _R>&& NGS_LIB_MODULE_NAME::_detail::multipiable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END