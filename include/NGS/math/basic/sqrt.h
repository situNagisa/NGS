#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

template<cpt::real_number _Type>
constexpr _Type sqrt(_Type x) noexcept {
	if (std::is_constant_evaluated() && !(x < static_cast<_Type>(0.0))) {
		if (x == static_cast<_Type>(0.0))
			return static_cast<_Type>(0.0);
		_Type r = x;
		_Type p = x / static_cast<_Type>(2.0);
		while (r != p) {
			r = p;
			p = (x / p + p) / static_cast<_Type>(2.0);
		}
		return r;
	}
	else {
		return static_cast<_Type>(std::sqrt(x));
	}
}

NGS_MATH_BASIC_END
