#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _details
{
	NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(high);
	NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(low);
}

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(output_gpio auto&& gpio) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (::std::invocable<decltype(_details::high), decltype(gpio)>)
		{
			return _details::high(NGS_PP_PERFECT_FORWARD(gpio));
		}
		else
		{
			return set(NGS_PP_PERFECT_FORWARD(gpio), level::high);
		}
	}
}high{};

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(output_gpio auto&& gpio) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (::std::invocable<decltype(_details::low), decltype(gpio)>)
		{
			return _details::low(NGS_PP_PERFECT_FORWARD(gpio));
		}
		else
		{
			return set(NGS_PP_PERFECT_FORWARD(gpio), level::low);
		}
	}
}low{};

NGS_LIB_MODULE_END