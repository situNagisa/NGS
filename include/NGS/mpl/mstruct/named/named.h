#pragma once

#include "../struct.h"
#include "./field.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<layout::align auto Align, named_field... Fields>
struct named_struct : structs::opaque_struct_mirror<Align,named_pair_field_t<Fields>...>
{
	using named_fields_type = ::boost::fusion::vector<Fields...>;
};

NGS_LIB_MODULE_END