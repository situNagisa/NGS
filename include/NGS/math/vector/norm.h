#pragma once

#include "./product.h"

NGS_LIB_BEGIN

template<class _V> requires inner_productable<_V, _V>
constexpr auto norm_squared(_V&& vector)
{
	return NGS_LIB_NAME::product_inner(vector, vector);
}

template<class _V> requires inner_productable<_V, _V>
constexpr auto norm(_V&& vector)
{
	return NGS_MATH_NS::sqrt(NGS_LIB_NAME::norm_squared(vector));
}

NGS_LIB_END