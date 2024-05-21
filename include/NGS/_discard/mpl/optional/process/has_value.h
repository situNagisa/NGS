#pragma once

#include "../defined.h"

NGS_MPL_OPTIONAL_BEGIN

template<class _T>
inline constexpr bool has_value = true;

template<>
inline constexpr bool has_value<type_traits::na> = false;

NGS_MPL_OPTIONAL_END