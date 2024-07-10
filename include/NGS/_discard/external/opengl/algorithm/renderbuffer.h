#pragma once

#include "../enum.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<auto Renderbuffer>
void renderbuffer_storage(const contexts::basic_renderbuffer<Renderbuffer>& renderbuffer, enums::internal_format format,::std::size_t width,::std::size_t height)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(renderbuffer);
	NGS_EXTERNAL_OPENGL_CHECK(::glRenderbufferStorage(
		static_cast<GLenum>(type_traits::object_t<decltype(renderbuffer)>::target),
		static_cast<GLenum>(format),
		static_cast<GLsizei>(width), 
		static_cast<GLsizei>(height)
	));
}

NGS_LIB_MODULE_END