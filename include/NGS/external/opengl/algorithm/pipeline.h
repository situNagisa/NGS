#pragma once

#include "../context.h"
#include "./vertex.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto install_buffer(cpt::derived_from_specialization<contexts::vertex_buffer> auto&& buffer, size_t index, ::std::span<const attribute> attributes)
	{
		using descriptor_type = typename type_traits::object_t<decltype(buffer)>::vertex_struct_type;
		basic::bind(NGS_PP_PERFECT_FORWARD(buffer));
		::std::span<const attribute> buffer_attributes = ::std::ranges::subrange(attributes.begin() + static_cast<::std::ptrdiff_t>(index), attributes.begin() + static_cast<::std::ptrdiff_t>(index) + mpl::mstruct::field_count_v<descriptor_type>);
		for (const auto& [count, type, normalized, stride, offset] : buffer_attributes) {
			NGS_EXTERNAL_OPENGL_CHECK(::glEnableVertexAttribArray(static_cast<GLuint>(index)));
			NGS_EXTERNAL_OPENGL_CHECK(::glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(count), type, normalized, static_cast<GLsizei>(stride), reinterpret_cast<void_ptr_cst>(offset)));
			index++;
		}
		return index;
	};
}

void pipeline_layout(const contexts::vertex_array& vertex_array, bool normalized, cpt::derived_from_specialization<contexts::vertex_buffer> auto&&... buffers)
{
	auto attributes = NGS_LIB_MODULE_NAME::vertex_descriptor<typename type_traits::object_t<decltype(buffers)>::vertex_struct_type...>(normalized);
	size_t index = 0;
	((index = _detail::install_buffer(NGS_PP_PERFECT_FORWARD(buffers), index, attributes)), ...);
}

void pipeline_layout(const contexts::vertex_array& vertex_array, cpt::derived_from_specialization<contexts::vertex_buffer> auto&&... buffers)
{
	NGS_LIB_MODULE_NAME::pipeline_layout(vertex_array, false, NGS_PP_PERFECT_FORWARD(buffers)...);
}
void pipeline_layout(const contexts::vertex_array& array, bool normalized, stl::tuples::tuple_like auto&& buffers)
{
	[] <size_t... I>(::std::index_sequence<I...>, const contexts::vertex_array & array, bool normalized, auto && buffers) {
		NGS_LIB_MODULE_NAME::pipeline_layout(array, normalized, ::std::get<I>(buffers)...);
	}(
		::std::make_index_sequence<::std::tuple_size_v<type_traits::naked_t<decltype(buffers)>>>{},
		array,
		normalized,
		NGS_PP_PERFECT_FORWARD(buffers)
		);
}
void pipeline_layout(const contexts::vertex_array& array, stl::tuples::tuple_like auto&& buffers)
{
	NGS_LIB_MODULE_NAME::pipeline_layout(array, false, NGS_PP_PERFECT_FORWARD(buffers));
}

NGS_LIB_MODULE_END