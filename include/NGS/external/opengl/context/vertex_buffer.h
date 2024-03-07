#pragma once

#include "../basic.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept vertex_buffer_descriptor = mpl::mstruct::flattened_structure<T> && mpl::mstruct::storage_structure<T>;

using basic_vertex_buffer = buffer<enums::buffer_target::array>;

template<vertex_buffer_descriptor VertexStruct>
struct vertex_buffer : basic_vertex_buffer
{
	NGS_MPL_ENVIRON2(vertex_buffer, basic_vertex_buffer);
public:
	using vertex_struct_type = VertexStruct;

	using base_type::base_type;
	using base_type::operator=;
};


NGS_LIB_MODULE_END