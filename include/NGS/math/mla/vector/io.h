#pragma once

#include "NGS/math/mla/vector/expression/expression.h"

NGS_BEGIN

template<mla::CVectorExpression _Expression>
constexpr std::string to_string(const _Expression& expr) {
	std::string str = "{";
	for (auto it = std::ranges::begin(expr); it != std::ranges::end(expr); ++it)
	{
		str += std::to_string(*it) + ((it != std::ranges::end(expr) - 1) ? ", " : "");
	}

	str += "}";
	return str;
}

NGS_END
