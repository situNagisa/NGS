#pragma once

#include "./defined.h"

NGS_COLOR_BEGIN



template<class _T, class _O = type_traits::object_t<_T>>
concept CPrimary = requires
{
	typename _O::alpha_type;
	typename _O::red_type;
	typename _O::green_type;
	typename _O::blue_type;

	{ _O::alpha() } -> std::convertible_to<typename _O::>
};

NGS_COLOR_END