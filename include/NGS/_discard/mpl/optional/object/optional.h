#pragma once

#include "../process.h"

NGS_MPL_OPTIONAL_BEGIN

template<class _T>
struct optional
{
	constexpr static bool has_value = options::has_value<_T>;
	using value = options::value<_T>;
	template<class _Default>
	using value_or = options::value_or<_T, _Default>;
};

NGS_MPL_OPTIONAL_END