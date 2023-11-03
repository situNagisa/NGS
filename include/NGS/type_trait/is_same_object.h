#pragma once

#include "./defined.h"
#include "./object.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Left, class _Right>
struct is_same_object : std::bool_constant<std::is_same_v<object_t<_Left>, object_t<_Right>>> {};
template<class _Left, class _Right>
constexpr bool is_same_object_v = is_same_object<_Left, _Right>::value;

NGS_TYPE_TRAIT_END
