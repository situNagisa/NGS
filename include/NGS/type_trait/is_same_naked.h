#pragma once

#include "./defined.h"
#include "./naked.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Left, class _Right>
struct is_same_naked : std::bool_constant<std::is_same_v<naked_t<_Left>, naked_t<_Right>>>{};

template<class _Left, class _Right>
constexpr bool is_same_naked_v = is_same_naked<_Left, _Right>::value;

NGS_TYPE_TRAIT_END
