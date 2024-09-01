#pragma once

#include "./defined.h"
#include "./naked.h"

NGS_CPT_BEGIN

template<class _T, class _O = type_traits::naked_t<_T>>
concept is_na = naked_same_as<_O, type_traits::na>;

template<class _T, class _O = type_traits::naked_t<_T>>
concept not_na = !is_na<_T>;

NGS_CPT_END