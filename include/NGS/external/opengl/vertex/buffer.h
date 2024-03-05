#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct vertex_buffer_struct {};
template<class T>
using vertex_buffer_struct_t = typename vertex_buffer_struct<T>::type;

template<class T> requires requires{ typename type_traits::object_t<T>::vertex_struct_type; }
struct vertex_buffer_struct<T> { using type = typename type_traits::object_t<T>::vertex_struct_type; };

template<class T>
concept vertex_buffer_descriptor = mpl::mstruct::flattened_structure<T>;

template<class T>
concept vertex_buffer = basic::bindable<T> && vertex_buffer_descriptor<vertex_buffer_struct_t<T>>;

template<vertex_buffer_descriptor VertexStruct>
struct buffer : buffers::unique_buffer<enums::buffer_target::array, VertexStruct>
{
	NGS_MPL_ENVIRON2(buffer, buffers::unique_buffer<enums::buffer_target::array, VertexStruct>);
public:
	using vertex_struct_type = VertexStruct;

	using base_type::base_type;
	using base_type::operator=;
};


NGS_LIB_MODULE_END