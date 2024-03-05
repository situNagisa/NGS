#pragma once

#include "../basic.h"
#include "./descriptor.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vertex_array : basic::context
{
	NGS_MPL_ENVIRON(vertex_array);
public:

	struct machine_type : bases::singleton<machine_type>
	{
		using context_type = vertex_array;

		void bind(const context_type& context) const
		{
			NGS_EXTERNAL_OPENGL_CHECK(::glBindVertexArray(context.get_context()));
		}
	};
private:
	static auto _create()
	{
		context_t vertex_array;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenVertexArrays(1, &vertex_array));
		return vertex_array;
	
	}
public:
	vertex_array(): base_type(_create()) {}
	~vertex_array()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteVertexArrays(1, &get_context()));
	}
};

namespace _detail
{
	auto install_buffer(vertex_buffer auto&& buffer, size_t index, ::std::span<const attribute> attributes)
	{
		using descriptor_type = vertex_buffer_struct_t<decltype(buffer)>;
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

void commit_layout(vertex_array& vertex_array, bool normalized, vertex_buffer auto&&... buffers)
{
	basic::bind(vertex_array);
	auto attributes = NGS_LIB_MODULE_NAME::create_vertex_descriptor<vertex_buffer_struct_t<decltype(buffers)>...>(normalized);
	size_t index = 0;
	((index = _detail::install_buffer(NGS_PP_PERFECT_FORWARD(buffers), index, attributes)), ...);
}
void commit_layout(vertex_array& vertex_array, vertex_buffer auto&&... buffers)
{
	NGS_LIB_MODULE_NAME::commit_layout(vertex_array, false, NGS_PP_PERFECT_FORWARD(buffers)...);
}
void commit_layout(vertex_array& array,bool normalized, stl::tuples::tuple_like auto&& buffers)
{
	[]<size_t... I>(::std::index_sequence<I...>, vertex_array& array, bool normalized, auto&& buffers) {
		NGS_LIB_MODULE_NAME::commit_layout(array, normalized, ::std::get<I>(buffers)...);
	}(
		::std::make_index_sequence<::std::tuple_size_v<type_traits::naked_t<decltype(buffers)>>>{},
		array,
		normalized,
		NGS_PP_PERFECT_FORWARD(buffers)
	);
}
void commit_layout(vertex_array& array, stl::tuples::tuple_like auto&& buffers)
{
	NGS_LIB_MODULE_NAME::commit_layout(array, false, NGS_PP_PERFECT_FORWARD(buffers));
}

NGS_LIB_MODULE_END