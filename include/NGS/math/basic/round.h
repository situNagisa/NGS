#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

template<class _T>
constexpr _T round(_T x)
{
	using type = _T;
	if constexpr (::std::floating_point<type>)
	{
		if (::std::is_constant_evaluated())
		{

			return static_cast<type>(static_cast<::std::int64_t>(x + static_cast<type>(0.5)));
		}
		else
		{
			return ::std::round(x);
		}
	}
	else
	{
		return x;
	}
}

NGS_MATH_BASIC_END