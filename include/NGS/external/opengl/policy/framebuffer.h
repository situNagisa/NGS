#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../context.h"
#include "./texture.h"
#include "./renderbuffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::framebuffer_target Target, enums::framebuffer_attachment... Attachments>
struct basic_framebuffer
{
	NGS_MPL_ENVIRON_BEGIN(basic_framebuffer);
public:
	using context_type = contexts::basic_framebuffer<Target>;

	template<enums::framebuffer_attachment Attachment, auto Texture>
	static void _attach(const context_type& context, const basic_texture<Texture>& texture, ::std::size_t mipmap_level)
	{
		algorithm::framebuffer_set_texture_2d<Attachment>(context, texture.get_context(), mipmap_level);
	}
	template<enums::framebuffer_attachment Attachment, auto Texture>
	static void _attach(const context_type& context, const basic_texture<Texture>& texture) { self_type::template _attach<Attachment>(context, texture, 0); }

	template<enums::framebuffer_attachment Attachment, auto Renderbuffer>
	static void _attach(const context_type& context, const basic_renderbuffer<Renderbuffer>& renderbuffer)
	{
		algorithm::framebuffer_set_renderbuffer<Attachment>(context, renderbuffer.get_context());
	}

	template<class T, enums::framebuffer_attachment Attachment>
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
		basic::bind(_context);
		self_type::attach(NGS_PP_PERFECT_FORWARD(attachments)...);
	}

	void attach(auto&&... attachments)
		requires (sizeof...(attachments) == sizeof...(Attachments)) && (self_type::template _is_attachable<decltype(attachments), Attachments>() && ...)
	{
		(self_type::template _attach<Attachments>(_context, NGS_PP_PERFECT_FORWARD(attachments)),...);
		::std::array framebuffer_attachments{ Attachments... };
		auto is_not_color_attachment = [](enums::framebuffer_attachment attachment)
		{
			return !(static_cast<gl_enum_t>(attachment) >= static_cast<gl_enum_t>(enums::framebuffer_attachment::color0) && static_cast<gl_enum_t>(attachment) <= static_cast<gl_enum_t>(enums::framebuffer_attachment::color15));
		};
		auto none_color_attachments = ::std::ranges::remove_if(framebuffer_attachments, is_not_color_attachment);
		algorithm::framebuffer_set_draw_buffers(_context, ::std::span{ ::std::ranges::begin(framebuffer_attachments) , ::std::ranges::size(framebuffer_attachments) - ::std::ranges::size(none_color_attachments)});
		NGS_ASSERT(algorithm::framebuffer_get_status(_context) == enums::framebuffer_status::complete);
	}

	constexpr auto&& get_context()const { return _context; }

	context_type _context;
};

template<enums::framebuffer_attachment... Attachments>
using framebuffer = basic_framebuffer<enums::framebuffer_target::framebuffer, Attachments...>;

template<enums::framebuffer_attachment... Attachments>
using read_framebuffer = basic_framebuffer<enums::framebuffer_target::read, Attachments...>;

template<enums::framebuffer_attachment... Attachments>
using draw_framebuffer = basic_framebuffer<enums::framebuffer_target::draw, Attachments...>;

NGS_LIB_MODULE_END