#pragma once

#include "NGS/math/defined.h"

NGS_MATH_BEGIN

constexpr auto inversion_number(const std::ranges::forward_range auto& sequence) {
	size_t result = 0;
	for (auto it1 = std::ranges::begin(sequence); it1 != std::ranges::end(sequence); ++it1) {
		for (auto it2 = it1; it2 != std::ranges::end(sequence); ++it2) {
			if (*it1 > *it2)++result;
		}
	}
	return result;
}
constexpr auto inversion_number(const std::convertible_to<size_t> auto&... sequence) {
	return inversion_number(std::array<size_t, sizeof...(sequence)>(sequence...);
}

NGS_MATH_END
