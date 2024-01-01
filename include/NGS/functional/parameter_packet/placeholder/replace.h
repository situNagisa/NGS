#pragma once

#include "./concept.h"
#include "./placeholder.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<size_t _AimIndex, size_t _CurrentIndex = 0>
	constexpr decltype(auto) get_param(auto&& first, auto&&... rest)
	{
		NGS_ASSERT_IF_CONSTEXPR(_CurrentIndex <= _AimIndex, "placeholder index out of range")
		{
			if constexpr (_AimIndex == _CurrentIndex)
			{
				return NGS_PP_PERFECT_FORWARD(first);
			}
			else if constexpr (sizeof...(rest))
			{
				return _detail::get_param<_AimIndex, _CurrentIndex + 1>(NGS_PP_PERFECT_FORWARD(rest)...);
			}
		}
	}
}

constexpr decltype(auto) replace(is_placeholder auto&& param, auto&&... params)
{
	constexpr auto index = type_traits::object_t<decltype(param)>::value - 1;
	NGS_ASSERT_IF_CONSTEXPR(index < sizeof...(params),
		"placeholder index is out of range, "
		"are you sure you have enough arguments when you call replace?"
	)
	{
		return _detail::get_param<index, 0>(NGS_PP_PERFECT_FORWARD(params)...);
	}
}


NGS_LIB_MODULE_END