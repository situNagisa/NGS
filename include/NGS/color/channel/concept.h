#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept color_channel = requires{
	{ _O::count } -> std::convertible_to<size_t>;
	{ _O::offset } -> std::convertible_to<size_t>;
	{ _O::filter } -> std::convertible_to<size_t>;
	{ _O::filter_with_offset } -> std::convertible_to<size_t>;
		requires std::integral<typename _O::type>;
};

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(color_channel);
