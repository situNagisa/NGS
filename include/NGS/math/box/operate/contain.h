#pragma once

#include "../concept.h"
#include "./range.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<box _T>
constexpr bool contain(const _T& t, vectors::vector_with_extent<vectors::extent_v<_T>> auto&& point)
{
	using box_type = _T;
	using point_type = decltype(point);
	constexpr auto dimension = vectors::extent_v<box_type>;

	size_t i = 0;
	for (auto&& inter : t)
	{
		if (!inter.contain(vectors::ops::access(NGS_PP_PERFECT_FORWARD(point), i)))
			return false;
		i++;
	}
	return true;
}

NGS_LIB_MODULE_END