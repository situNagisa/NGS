#pragma once

#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct basic_vertex_array
{
public:

public:
	basic_vertex_array(::std::ranges::random_access_range auto&& vertex_descriptor)
		requires ::std::convertible_to<::std::ranges::range_value_t<decltype(vertex_descriptor)>,attribute>
	{

	}
};

NGS_LIB_MODULE_END