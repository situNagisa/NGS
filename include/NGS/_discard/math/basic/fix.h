#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

constexpr auto fix(concepts::fundamental auto number)
{
	using type = std::remove_cvref_t<decltype(number)>;
	if constexpr (std::is_integral_v<type>)
	{
		return number;
	}
	else
	{
		return static_cast<type>(static_cast<::std::intmax_t>(number));
	}
}

NGS_MATH_BASIC_END