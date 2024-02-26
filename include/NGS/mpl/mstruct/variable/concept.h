#pragma once

#include "./value.h"
#include "./size.h"
#include "./align.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept variable = requires() {
	typename variable_value_t<T>;
	{ variable_size_v<T> } -> ::std::convertible_to<::std::size_t>;
	{ variable_align_v<T> } -> layout::align;
};

NGS_LIB_MODULE_END
