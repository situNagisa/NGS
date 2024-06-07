#pragma once

#include "./max_dimension.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, dimension_t Depth>
struct subtensor
{
	static_assert(Depth == 0, "depth is too deep");
	using type = T;
};

template<class T, dimension_t Depth>
using subtensor_t = typename subtensor<T, Depth>::type;

template<class T>
struct subtensor<T, 0> { using type = T; };

template<dimension_t Depth, class T> requires (Depth > 0)
struct subtensor<T, Depth>
{
	using type = subtensor_t<::std::ranges::range_value_t<T>, Depth - 1>;
};

NGS_LIB_MODULE_END