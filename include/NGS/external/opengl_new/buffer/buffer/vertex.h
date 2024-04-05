#pragma once

#include "../../basic.h"
#include "../descriptor.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::ranges::contiguous_range Range>
	requires buffer_descriptor<::std::ranges::range_value_t<Range>>
struct vertex_buffer : buffer<NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::vertex_buffer, Range>
{
	NGS_MPL_ENVIRON2(vertex_buffer, buffer<NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::vertex_buffer, Range>);
public:
	using base_type::base_type;
	using base_type::operator=;
};

template<::std::ranges::contiguous_range Range> requires buffer_descriptor<::std::ranges::range_value_t<Range>>
vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage, Range&&) -> vertex_buffer<type_traits::naked_t<Range>>;

template<::std::ranges::contiguous_range Range> requires buffer_descriptor<::std::ranges::range_value_t<Range>>
vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage, const Range&) -> vertex_buffer<type_traits::naked_t<Range>>;

template<buffer_descriptor Buffer, ::std::size_t VertexCount>
decltype(auto) make_array_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&&... array_args)
	requires ::std::constructible_from<::std::array<Buffer, VertexCount>, decltype(array_args)...>
{
	return vertex_buffer(usage, ::std::array<Buffer, VertexCount>{NGS_PP_PERFECT_FORWARD(array_args)...});
}

template<buffer_descriptor Buffer, ::std::size_t VertexCount>
decltype(auto) make_span_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, ::std::span< Buffer,VertexCount> data)
{
	return vertex_buffer(usage, data);
}

template<buffer_descriptor Buffer>
decltype(auto) make_span_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, ::std::span< Buffer> data)
{
	return vertex_buffer(usage, data);
}

template<buffer_descriptor Buffer, ::std::size_t VertexCount>
decltype(auto) make_span_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, type_traits::add_cv_like_t<Buffer, void>* data)
{
	return vertex_buffer(usage, ::std::span{ reinterpret_cast<Buffer*>(data), VertexCount});
}

template<buffer_descriptor Buffer>
decltype(auto) make_span_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, type_traits::add_cv_like_t<Buffer, void>* data, ::std::size_t vertex_count)
{
	return vertex_buffer(usage, ::std::span{ reinterpret_cast<Buffer*>(data), vertex_count});
}

template<buffer_descriptor Buffer>
decltype(auto) make_vector_vertex_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&&... range_args)
	requires ::std::constructible_from<::std::vector<Buffer>, decltype(range_args)...>
{
	return vertex_buffer(usage, ::std::vector<Buffer>{ NGS_PP_PERFECT_FORWARD(range_args)...});
}

NGS_LIB_MODULE_END
