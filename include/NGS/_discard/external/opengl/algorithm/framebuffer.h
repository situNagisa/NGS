#pragma once

#include "../error.h"
#include "../enum.h"
#include "../basic.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::framebuffer_attachment Attachment, auto Framebuffer,auto Renderbuffer>
void framebuffer_set_renderbuffer(const contexts::basic_framebuffer<Framebuffer>& framebuffer,const contexts::basic_renderbuffer<Renderbuffer>& renderbuffer)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(framebuffer);
	NGS_EXTERNAL_OPENGL_CHECK(::glFramebufferRenderbuffer(
		static_cast<GLenum>(type_traits::object_t<decltype(framebuffer)>::target),
		static_cast<GLenum>(Attachment),
		static_cast<GLenum>(type_traits::object_t<decltype(renderbuffer)>::target),
		renderbuffer.get_context()
	));
}

template<enums::framebuffer_attachment Attachment, auto Framebuffer, auto Texture>
void framebuffer_set_texture_2d(const contexts::basic_framebuffer<Framebuffer>& framebuffer, const contexts::basic_texture<Texture>& texture, ::std::size_t mipmap_level = 0)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(framebuffer);
	NGS_EXTERNAL_OPENGL_CHECK(::glFramebufferTexture2D(
		static_cast<GLenum>(type_traits::object_t<decltype(framebuffer)>::target),
		static_cast<GLenum>(Attachment),
		static_cast<GLenum>(type_traits::object_t<decltype(texture)>::target),
		texture.get_context(),
		mipmap_level
	));
}

template<auto Framebuffer>
auto framebuffer_get_status(const contexts::basic_framebuffer<Framebuffer>& framebuffer)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(framebuffer);
	GLenum status;
	NGS_EXTERNAL_OPENGL_CHECK(status = ::glCheckFramebufferStatus(static_cast<GLenum>(type_traits::object_t<decltype(framebuffer)>::target)));
	return static_cast<enums::framebuffer_status>(status);
}

template<auto Framebuffer>
void framebuffer_set_draw_buffers(const contexts::basic_framebuffer<Framebuffer>& framebuffer, const ::std::ranges::contiguous_range auto& attachments)
	requires ::std::same_as<::std::add_const_t<::std::ranges::range_value_t<decltype(attachments)>>,const enums::framebuffer_attachment>
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(framebuffer);
	NGS_EXTERNAL_OPENGL_CHECK(::glDrawBuffers(static_cast<GLsizei>(::std::ranges::size(attachments)), reinterpret_cast<const GLenum*>(::std::ranges::data(attachments))));
}


NGS_LIB_MODULE_END