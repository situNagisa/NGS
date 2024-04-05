#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept color_channel = requires{
	{ type_traits::object_t<T>::count } -> std::convertible_to<size_t>;
	{ type_traits::object_t<T>::offset } -> std::convertible_to<size_t>;
	{ type_traits::object_t<T>::filter } -> std::convertible_to<size_t>;
	{ type_traits::object_t<T>::filter_with_offset } -> std::convertible_to<size_t>;
		requires std::integral<typename type_traits::object_t<T>::type>;
};

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(color_channel);
