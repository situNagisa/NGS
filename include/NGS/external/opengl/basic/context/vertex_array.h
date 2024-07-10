#pragma once

#include "../config.h"
#include "./basic.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto vertex_array_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenVertexArrays(1, &context));
		return context;
	}
	void vertex_array_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteVertexArrays(1, &context));
	}
	void vertex_array_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindVertexArray(context));
	}
	NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(basic_vertex_array, _detail::vertex_array_creator, _detail::vertex_array_deleter, _detail::vertex_array_binder);
}

struct vertex_array : _detail::basic_vertex_array
{
	NGS_PP_INJECT(vertex_array);
public:
	using base_type::base_type;
	using base_type::operator=;

	void draw_array(enums::draw_mode draw_mode, ::std::size_t count, ::std::size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glDrawArrays(static_cast<GLenum>(draw_mode), static_cast<GLint>(offset), static_cast<GLsizei>(count)));
	}

	void draw_elements(enums::element_draw_mode draw_mode, ::std::size_t count, enums::buffer_indices_fundamental type, ::std::size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glDrawElements(static_cast<GLenum>(draw_mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), reinterpret_cast<const void*>(offset)));
	}
};


NGS_LIB_MODULE_END