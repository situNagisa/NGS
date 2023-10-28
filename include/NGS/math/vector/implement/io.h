#pragma once

#include "NGS/math/vector/concept.h"

NGS_BEGIN

constexpr std::string to_string(math::vectors::functor::expression auto&& expr) {
	std::string str = "{";

	for (auto it = std::ranges::begin(expr); it != std::ranges::end(expr); ++it)
	{
		str += to_string(*it) + ((it != std::ranges::end(expr) - 1) ? ", " : "");
	}

	str += "}";
	return str;
}

NGS_END