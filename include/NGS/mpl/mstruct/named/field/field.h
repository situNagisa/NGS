#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct named_pair_field {};
template<class Field>
using named_pair_field_t = typename named_pair_field<Field>::type;

template<class Field> requires requires{ typename type_traits::object_t<Field>::field_type; }
struct named_pair_field<Field>
{
	using type = typename type_traits::object_t<Field>::field_type;
};


NGS_LIB_MODULE_END