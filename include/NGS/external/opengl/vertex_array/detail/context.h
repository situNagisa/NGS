#pragma once

#include "./attribute.h"
#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto vertex_array_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenVertexArrays(1, &context));
		return context;
	}
	void vertex_array_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteVertexArrays(1, &context));
	}
	void vertex_array_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBindVertexArray(context));
	}
	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BINDABLE_CONTEXT(basic_vertex_array, _detail::vertex_array_creator, _detail::vertex_array_deleter, _detail::vertex_array_binder);
}

struct context : _detail::basic_vertex_array
{
	NGS_PP_INJECT(context);
public:
	using base_type::base_type;
	using base_type::operator=;

	template<buffer_descriptor Descriptor>
	auto _install_buffer(buffers::buffer_context auto&& buffer, size_t index, ::std::span<const attribute> attributes)
	{
		using descriptor_type = Descriptor;
		contextes::bind(NGS_PP_PERFECT_FORWARD(buffer));
		auto buffer_attributes = attributes.subspan(index, mpl::mstruct::field_count_v<descriptor_type>);
		for (const auto& [count, type, normalized, stride, offset] : buffer_attributes) {
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glEnableVertexAttribArray(static_cast<GLuint>(index)));
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(count), ::std::to_underlying(type), normalized, static_cast<GLsizei>(stride), reinterpret_cast<const void*>(offset)));
			index++;
		}
		return index;
	}

	template<buffer_descriptor... Descriptor>
	void layout(bool normalized, buffers::buffer_context auto&&... buffers)
		requires (sizeof...(Descriptor) == sizeof...(buffers))
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		auto attributes = NGS_LIB_MODULE_NAME::vertex_descriptor<Descriptor...>(normalized);
		size_t index = 0;
		((index = self_type::_install_buffer<Descriptor>(NGS_PP_PERFECT_FORWARD(buffers), index, attributes)), ...);
	}

	void draw_array(enums::draw_mode draw_mode, ::std::size_t count, ::std::size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDrawArrays(::std::to_underlying(draw_mode), static_cast<GLint>(offset), static_cast<GLsizei>(count)));
	}

	void draw_elements(enums::element_draw_mode draw_mode, ::std::size_t count, enums::buffer_indices_fundamental type, ::std::size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDrawElements(::std::to_underlying(draw_mode), static_cast<GLsizei>(count), ::std::to_underlying(type), reinterpret_cast<const void*>(offset)));
	}
};

template<buffer_descriptor... Descriptor>
decltype(auto) make_layout_array(bool normalized, buffers::buffer_context auto&&... buffers)
{
	auto vertex_array = context{};
	contextes::bind(vertex_array);
	vertex_array.layout<Descriptor...>(normalized, NGS_PP_PERFECT_FORWARD(buffers)...);
	return vertex_array;
}

NGS_LIB_MODULE_END