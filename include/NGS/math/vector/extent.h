#pragma once

#include "./index.h"
#include "./anchor.h"
#include "./defined.h"

NGS_LIB_BEGIN

using extent_t = ::std::size_t;

constexpr extent_t dynamic_extent = ::std::numeric_limits<extent_t>::max();
constexpr extent_t adapter_extent = ::std::numeric_limits<extent_t>::max() - 1;

template<class _V>
struct extent : ::std::integral_constant<extent_t, dynamic_extent> {};

template<class _V>
constexpr extent_t extent_v = extent<_V>::value;

namespace detail
{
	template<class _V>
	concept has_extent = requires { { type_traits::object_t<_V>::extent } -> ::std::convertible_to<extent_t>; };
}

template<class _V> requires detail::has_extent<_V>
struct extent<_V> : ::std::integral_constant<extent_t, type_traits::object_t<_V>::extent> {};

NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY_ENV(extent);

NGS_LIB_END