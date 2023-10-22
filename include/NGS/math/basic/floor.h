#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

constexpr auto floor(cpt::real_number auto number)
{
	if (std::is_constant_evaluated())
	{
		using type = std::remove_cvref_t<decltype(number)>;
		if constexpr (std::is_integral_v<type>)
		{
			return number;
		}
		else
		{
			return static_cast<type>(static_cast<int64>(number) - (number < 0.0));
		}
	}
	else
	{
		return std::floor(number);
	}
}

NGS_MATH_BASIC_END