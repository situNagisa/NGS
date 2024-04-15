#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using bits::bitsets::underlying_type;
using bits::bitsets::underlying_type_t;

template<class T>
struct fields {};

template<class T> requires requires{ { type_traits::object_t<T>::fields() }; }
struct fields<T>
{
	constexpr static decltype(auto) value() { return type_traits::object_t<T>::fields(); }
};


template<class T> requires requires{ { fields<T>::value() }; }
constexpr decltype(auto) field_v()
{
	return fields<T>::value();
}



NGS_LIB_MODULE_END
