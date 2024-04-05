#pragma once

#include "../basic.h"
#include "../texture.h"
#include "../renderbuffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_target Target, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment... Attachments>
struct basic_framebuffer
{
	NGS_MPL_ENVIRON_BEGIN(basic_framebuffer);
public:
	using context_type = NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::basic_framebuffer<Target>;

	template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment Attachment, auto Texture>
	static void _attach(const context_type& context, const NGS_EXTERNAL_OPENGL_TEXTURE_NS::basic_texture<Texture>& texture, ::std::size_t mipmap_level)
	{
		context.template set_texture_2d<Attachment>(texture.get_context(), mipmap_level);
	}
	template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment Attachment, auto Texture>
	static void _attach(const context_type& context, const NGS_EXTERNAL_OPENGL_TEXTURE_NS::basic_texture<Texture>& texture) { self_type::template _attach<Attachment>(context, texture, 0); }

	template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment Attachment, auto Renderbuffer>
	static void _attach(const context_type& context, const NGS_EXTERNAL_OPENGL_RENDERBUFFER_NS::basic_renderbuffer<Renderbuffer>& renderbuffer)
	{
		context.template set_renderbuffer<Attachment>(renderbuffer.get_context());
	}

	template<class T, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment Attachment>
	consteval static bool _is_attachable()
	{
		return requires(const context_type & context, T attachment)
		{
			{ self_type::template _attach<Attachment>(context, attachment) };
		};
	}

	explicit(false) basic_framebuffer(auto&&... attachments)
		requires (sizeof...(attachments) == sizeof...(Attachments)) && (self_type::template _is_attachable<decltype(attachments), Attachments>() && ...)
	{
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_context);
		self_type::attach(NGS_PP_PERFECT_FORWARD(attachments)...);
	}

	void attach(auto&&... attachments)
		requires (sizeof...(attachments) == sizeof...(Attachments)) && (self_type::template _is_attachable<decltype(attachments), Attachments>() && ...)
	{
		(self_type::template _attach<Attachments>(_context, NGS_PP_PERFECT_FORWARD(attachments)),...);
		::std::array framebuffer_attachments{ Attachments... };
		auto is_not_color_attachment = [](NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment attachment)
		{
			return !(static_cast<gl_enum_t>(attachment) >= static_cast<gl_enum_t>(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment::color0) && static_cast<gl_enum_t>(attachment) <= static_cast<gl_enum_t>(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment::color15));
		};
		auto none_color_attachments = ::std::ranges::remove_if(framebuffer_attachments, is_not_color_attachment);
		_context.set_draw_buffers(::std::span{ ::std::ranges::begin(framebuffer_attachments) , ::std::ranges::size(framebuffer_attachments) - ::std::ranges::size(none_color_attachments)});
		NGS_ASSERT(_context.get_status() == NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_status::complete);
	}

	void clear(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_clear_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(_context);
		NGS_EXTERNAL_OPENGL_CHECK(::glClear(static_cast<GLbitfield>(bit)));
	}

	void enable(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_enable_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(_context);
		NGS_EXTERNAL_OPENGL_CHECK(::glEnable(static_cast<GLenum>(bit)));
	}
	void disable(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_enable_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(_context);
		NGS_EXTERNAL_OPENGL_CHECK(::glDisable(static_cast<GLenum>(bit)));
	}

	void clear_color(colors::primary_color auto color) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(_context);
		//NGS_EXTERNAL_OPENGL_CHECK(::glClearColor(color.r, color.g, color.b, color.a));
	}

	void set_viewport(::std::size_t x, ::std::size_t y, ::std::size_t width, ::std::size_t height) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(_context);
		NGS_EXTERNAL_OPENGL_CHECK(::glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
	}

	constexpr auto&& get_context()const { return _context; }

	context_type _context;
};

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment... Attachments>
using framebuffer = basic_framebuffer<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_target::framebuffer, Attachments...>;

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment... Attachments>
using read_framebuffer = basic_framebuffer<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_target::read, Attachments...>;

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_attachment... Attachments>
using draw_framebuffer = basic_framebuffer<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::framebuffer_target::draw, Attachments...>;

NGS_LIB_MODULE_END