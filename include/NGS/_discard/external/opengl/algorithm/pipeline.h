#pragma once

#include "../context.h"
#include "./vertex.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<contexts::vertex_buffer_descriptor Descriptor>
	auto install_buffer(cpt::naked_same_as<contexts::vertex_buffer> auto&& buffer, size_t index, ::std::span<const attribute> attributes)
	{
		using descriptor_type = Descriptor;
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

template<contexts::vertex_buffer_descriptor... Descriptor>
void pipeline_layout(const contexts::vertex_array& vertex_array, bool normalized, cpt::naked_same_as<contexts::vertex_buffer> auto&&... buffers)
	requires (sizeof...(Descriptor) == sizeof...(buffers))
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(vertex_array);
	auto attributes = NGS_LIB_MODULE_NAME::vertex_descriptor<Descriptor...>(normalized);
	size_t index = 0;
	((index = _detail::install_buffer<Descriptor>(NGS_PP_PERFECT_FORWARD(buffers), index, attributes)), ...);
}

template<contexts::vertex_buffer_descriptor... Descriptor>
void pipeline_layout(const contexts::vertex_array& vertex_array, cpt::naked_same_as<contexts::vertex_buffer> auto&&... buffers)
{
	NGS_LIB_MODULE_NAME::pipeline_layout< Descriptor...>(vertex_array, false, NGS_PP_PERFECT_FORWARD(buffers)...);
}

NGS_LIB_MODULE_END