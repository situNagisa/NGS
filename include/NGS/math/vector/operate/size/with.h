#pragma once

#include "./defined.h"


NGS_LIB_MODULE_BEGIN



inline constexpr auto size = [](auto&& vector, auto&& with) requires !adapter_vector<decltype(vector)> || !adapter_vector<decltype(with)>
{
	if constexpr (adapter_vector<decltype(vector)>)
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(with));
	}
	else
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
	}
};


NGS_LIB_MODULE_END