#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

template<size_t _Dimension,class _ValueType>
struct scalar_adapter : yap::expression<scalar_adapter<_Dimension, _ValueType>>
{
	using value_type = _ValueType;
	constexpr static size_t dimension = _Dimension;

	constexpr scalar_adapter(value_type value) : value(value) {}

	constexpr auto access(size_t index) const { return value; }

	value_type value;
};

NGS_MATH_VECTOR_END