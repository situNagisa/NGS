#pragma once

#include "./static.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t index, input_or_output_vector auto&& vector, auto&& functor)const
		{
			return NGS_PP_PERFECT_FORWARD(functor)(index, NGS_PP_PERFECT_FORWARD(vector));
		}
	}dynamic_transform{};

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(input_or_output_vector auto&& vector, auto&&)const
		{
			return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
		}
	}dynamic_transform_sizer{};
}

template<input_or_output_vector _V, ::std::invocable<index_t, _V> _Functor>
using transform_dynamic_view = transform_view<extent_v<_V>, _detail::dynamic_transform, _detail::dynamic_transform_sizer, _V, _Functor>;

template<input_or_output_vector _V>
constexpr decltype(auto) transform(_V&& vector, ::std::invocable<index_t, _V> auto&& functor)
{
	return transform_dynamic_view<_V&&, decltype(functor)>(NGS_PP_PERFECT_FORWARD(vector), NGS_PP_PERFECT_FORWARD(functor));
}

NGS_LIB_MODULE_END