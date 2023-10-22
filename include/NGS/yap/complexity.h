#pragma once

#include "./concept.h"

NGS_YAP_BEGIN

template<class>
inline constexpr size_t complexity = 0;

template<class _Expression>
	requires requires{ { type_traits::object_t<_Expression>::complexity } -> std::convertible_to<size_t>; }
inline constexpr size_t complexity<_Expression> = type_traits::object_t<_Expression>::complexity;

NGS_YAP_END
