#pragma once

#include "./round.h"
#include "./defined.h"

#undef min

NGS_MATH_BASIC_BEGIN

template<class _T>
constexpr _T sqrt(_T x) noexcept {
	using type = _T;
	if constexpr (::std::floating_point<type>)
	{
		if (::std::is_constant_evaluated() && !(x < 0.0)) {
			if (x <= ::std::numeric_limits<type>::min())
				return static_cast<type>(0.0);

			float64 r = x;
			float64 p = x / static_cast<float64>(2.0);
			while ((r - p) > ::std::numeric_limits<float64>::min()) {
				r = p;
				p = (x / p + p) / static_cast<float64>(2.0);
			}

			return static_cast<type>(r);
		}
		else {
			return static_cast<type>(::std::sqrt(x));
		}
	}
	else if constexpr (::std::integral<type>)
	{
		return static_cast<type>(basic::round(basic::sqrt(static_cast<float64>(x))));
	}
	else
	{
		return ::std::sqrt(x);
	}
}

NGS_MATH_BASIC_END
