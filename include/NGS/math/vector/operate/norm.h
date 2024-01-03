#pragma once

#include "./product.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V> requires inner_productable<_V, _V>
constexpr auto norm_squared(_V&& vector)
{
	return NGS_LIB_MODULE_NAME::product_inner(vector, vector);
}

template<class _V> requires inner_productable<_V, _V>
constexpr auto norm(_V&& vector)
{
	return NGS_MATH_NS::sqrt(NGS_LIB_MODULE_NAME::norm_squared(vector));
}

template<class _V> requires inner_productable<_V, _V>
using norm_t = type_traits::object_t<decltype(norm(::std::declval<_V>()))>;

NGS_LIB_MODULE_END