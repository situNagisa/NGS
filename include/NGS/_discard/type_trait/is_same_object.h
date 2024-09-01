#pragma once

#include "./defined.h"
#include "./object.h"

NGS_TYPE_TRAIT_BEGIN

template<class Left, class Right>
struct is_same_object : std::bool_constant<std::is_same_v<object_t<Left>, object_t<Right>>> {};
template<class Left, class Right>
constexpr bool is_same_object_v = is_same_object<Left, Right>::value;

NGS_TYPE_TRAIT_END
