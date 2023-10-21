#pragma once

#include "./defined.h"
#include "./original.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Left, class _Right>
struct is_same_original
{
	constexpr static bool value = std::is_same_v<original_t<_Left>, original_t<_Right>>;
};
template<class _Left, class _Right>
constexpr bool is_same_original_v = is_same_original<_Left, _Right>::value;

NGS_TYPE_TRAIT_END
