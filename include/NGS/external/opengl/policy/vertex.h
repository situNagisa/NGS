#pragma once

#include "../context.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::ranges::contiguous_range Range>
	requires contexts::vertex_buffer_descriptor<::std::ranges::range_value_t<Range>>
struct vertex_buffer : buffer<contexts::vertex_buffer, Range>
{
	NGS_MPL_ENVIRON2(vertex_buffer, buffer<contexts::vertex_buffer, Range>);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END
