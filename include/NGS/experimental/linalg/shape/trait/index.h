#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct index
{
	using type = ::std::size_t;
};
template<class T>
	requires ::std::is_object_v<T> && requires{ typename T::index_type; }
struct index<T>
{
    using type = typename T::index_type;
};

template<class T>
using index_t = typename index<T>::type;

NGS_LIB_MODULE_END