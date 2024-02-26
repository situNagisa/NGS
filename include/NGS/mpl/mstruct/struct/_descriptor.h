#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct struct_descriptor{};
template<class T>
using struct_descriptor_t = typename struct_descriptor<T>::type;

template<class T> requires requires{ typename type_traits::object_t<T>::descriptor_type; }
struct struct_descriptor<T>
{
	using type = typename type_traits::object_t<T>::descriptor_type;
};

template<basic::structure T> requires !requires{ typename type_traits::object_t<T>::descriptor_type; }
struct struct_descriptor<T>
{
	using type = T;
};

NGS_LIB_MODULE_END