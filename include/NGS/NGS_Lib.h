#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"

NGS_BEGIN

template<typename T, typename Arg>
inline constexpr auto&& any_cast(const Arg& arg) {
	return const_cast<T>(*reinterpret_cast<const T*>(&arg));
}
NGS_END