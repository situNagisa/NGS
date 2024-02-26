#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct struct_named_fields {};
template<class Struct>
using struct_named_fields_t = typename struct_named_fields<Struct>::type;

template<class Struct> requires requires{ typename type_traits::object_t<Struct>::named_fields_type; }
struct struct_named_fields<Struct>
{
	using type = typename type_traits::object_t<Struct>::named_fields_type;
};


NGS_LIB_MODULE_END