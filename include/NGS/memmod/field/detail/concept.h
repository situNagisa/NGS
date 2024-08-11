#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept field = 
	concepts::object<T>
	&& layouts::align<decltype(align_v<T>)> && layouts::is_valid_align(align_v<T>)
	&& ::std::convertible_to<decltype(size_v<T>), ::std::size_t>;

NGS_LIB_MODULE_END