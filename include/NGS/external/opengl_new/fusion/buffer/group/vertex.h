#pragma once

#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<vertex_buffer>... Buffer>
struct vertex_group : buffer_group<Buffer...>
{
	NGS_MPL_ENVIRON2(vertex_group, buffer_group<Buffer...>);
public:
	using vertex_type = typename base_type::value_type;

	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END