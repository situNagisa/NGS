#pragma once

#include "../config.h"
#include "../enum.h"
#include "../error.h"
#include "./basic.h"
#include "./renderbuffer.h"
#include "./texture.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto framebuffer_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenFramebuffers(1, &context));
		return context;
	}
	void framebuffer_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteFramebuffers(1, &context));
	}
	template<enums::framebuffer_target Target>
	void framebuffer_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindFramebuffer(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_DEFINE_BASIC_CONTEXT(unknown_framebuffer, _detail::framebuffer_creator, _detail::framebuffer_deleter);
}

template<enums::framebuffer_target Target>
struct basic_framebuffer : _detail::unknown_framebuffer
{
	NGS_MPL_ENVIRON(basic_framebuffer);
public:
	constexpr static auto target = Target;
	using machine_type = context_machine<self_type, _detail::framebuffer_binder<target>>;


	template<enums::framebuffer_attachment Attachment, auto Renderbuffer>
	void set_renderbuffer(const basic_renderbuffer<Renderbuffer>& renderbuffer) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glFramebufferRenderbuffer(
			static_cast<GLenum>(target),
			static_cast<GLenum>(Attachment),
			static_cast<GLenum>(type_traits::object_t<decltype(renderbuffer)>::target),
			renderbuffer.get_handle()
		));
	}

	template<enums::framebuffer_attachment Attachment, auto Texture>
	void set_texture_2d(const basic_texture<Texture>& texture, ::std::size_t mipmap_level = 0) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glFramebufferTexture2D(
			static_cast<GLenum>(target),
			static_cast<GLenum>(Attachment),
			static_cast<GLenum>(type_traits::object_t<decltype(texture)>::target),
			texture.get_handle(),
			mipmap_level
		));
	}

	auto get_status() const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		GLenum status;
		NGS_EXTERNAL_OPENGL_CHECK(status = ::glCheckFramebufferStatus(static_cast<GLenum>(target)));
		return static_cast<enums::framebuffer_status>(status);
	}

	void set_draw_buffers(const ::std::ranges::contiguous_range auto& attachments) const
		requires ::std::same_as<::std::add_const_t<::std::ranges::range_value_t<decltype(attachments)>>, const enums::framebuffer_attachment>
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glDrawBuffers(static_cast<GLsizei>(::std::ranges::size(attachments)), reinterpret_cast<const GLenum*>(::std::ranges::data(attachments))));
	}
};

using framebuffer = basic_framebuffer<enums::framebuffer_target::framebuffer>;
using draw_framebuffer = basic_framebuffer<enums::framebuffer_target::draw>;
using read_framebuffer = basic_framebuffer<enums::framebuffer_target::read>;

NGS_LIB_MODULE_END