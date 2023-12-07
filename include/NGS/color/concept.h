#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template <class _T, class _O = type_traits::object_t<_T>>
concept color = requires() {
	true;
	//{ _O::format() } -> std::convertible_to<color_format>;
};

NGS_LIB_END
