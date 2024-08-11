#pragma once

#include "./defined.h"
#include "./naked.h"

NGS_TYPE_TRAIT_BEGIN

template<class Left, class Right>
struct is_same_naked : std::bool_constant<std::is_same_v<naked_t<Left>, naked_t<Right>>>{};

template<class Left, class Right>
constexpr bool is_same_naked_v = is_same_naked<Left, Right>::value;

NGS_TYPE_TRAIT_END
