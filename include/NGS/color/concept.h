#pragma once

#include "./defined.h"

NGS_COLOR_BEGIN

template <class _T, class _O = type_traits::object_t<_T>>
concept CColor = requires() {
	true;
	//{ _O::format() } -> std::convertible_to<color_format>;
};

NGS_COLOR_END
