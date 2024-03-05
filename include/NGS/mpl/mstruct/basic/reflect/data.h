#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
struct reflect_data {
	::std::size_t size;
	::std::size_t offset;
	T type;
};

NGS_LIB_MODULE_END