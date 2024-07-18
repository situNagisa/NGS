#pragma once

#include "./attachment.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto framebuffer_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenFramebuffers(1, &context));
		return context;
	}
	void framebuffer_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteFramebuffers(1, &context));
	}
	template<enums::framebuffer_target Target>
	void framebuffer_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBindFramebuffer(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BASIC_CONTEXT(unknown_framebuffer, _detail::framebuffer_creator, _detail::framebuffer_deleter);
}

template<enums::framebuffer_target Target>
struct basic_framebuffer : _detail::unknown_framebuffer
{
	NGS_PP_INJECT(basic_framebuffer);
public:
	constexpr static auto target = Target;
	using machine_type = contextes::context_machine<self_type, _detail::framebuffer_binder<target>>;

	basic_framebuffer() = default;

	basic_framebuffer(attachable auto&&... attachments) requires (sizeof...(attachments) != 0)
	{
		contextes::bind(*this);
		self_type::attach_all(NGS_PP_PERFECT_FORWARD(attachments)...);
	}

	template<enums::framebuffer_attachment Attachment>
	decltype(auto) attach(const textures::texture auto& texture, ::std::size_t mipmap_level = 0)
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glFramebufferTexture2D(
			::std::to_underlying(target),
			::std::to_underlying(Attachment),
			::std::to_underlying(type_traits::object_t<decltype(texture)>::target),
			texture.get_handle(),
			mipmap_level
		));
	}

	template<enums::framebuffer_attachment Attachment>
	decltype(auto) attach(const renderbuffers::renderable auto& renderbuffer)
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glFramebufferRenderbuffer(
			::std::to_underlying(target),
			::std::to_underlying(Attachment),
			::std::to_underlying(type_traits::object_t<decltype(renderbuffer)>::target),
			renderbuffer.get_handle()
		));
	}

	void attach(::std::span<const enums::framebuffer_attachment> attachments) const
	{
#if NGS_BUILD_TYPE_IS_DEBUG
		NGS_ASSERT(::std::ranges::all_of(attachments, enums::is_color_attachment));
#endif
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDrawBuffers(static_cast<GLsizei>(::std::ranges::size(attachments)), reinterpret_cast<const enums::enum_underlying_t*>(::std::ranges::data(attachments))));
	}

	decltype(auto) attach(attachable auto&& attachment)
	{
		using type = ::std::remove_cvref_t<decltype(attachment)>;
		return self_type::template attach<attachment_target_v<type>>(value(NGS_PP_PERFECT_FORWARD(attachment)));
	}

	decltype(auto) attach_all(attachable auto&&... attachments)
	{
		(self_type::attach(NGS_PP_PERFECT_FORWARD(attachments)), ...);
		constexpr auto draw_buffer = []
			{
				constexpr auto framebuffer_attachments = ::std::array{ attachment_target_v<::std::remove_cvref_t<decltype(attachments)>>... };
				constexpr auto size = ::std::ranges::count_if(framebuffer_attachments, enums::is_color_attachment);
				auto result = ::std::array<enums::framebuffer_attachment, size>{};
				::std::ranges::copy_if(framebuffer_attachments, ::std::ranges::begin(result), enums::is_color_attachment);
				return result;
			}();
		self_type::attach(draw_buffer);

		NGS_ASSERT(self_type::get_status() == enums::framebuffer_status::complete);
	}

	auto get_status() const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		GLenum status;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(status = ::glCheckFramebufferStatus(static_cast<GLenum>(target)));
		return static_cast<enums::framebuffer_status>(status);
	}

	void clear(enums::framebuffer_clear_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glClear(static_cast<GLbitfield>(bit)));
	}

	void enable(enums::framebuffer_enable_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glEnable(static_cast<GLenum>(bit)));
	}
	void disable(enums::framebuffer_enable_bit bit) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDisable(static_cast<GLenum>(bit)));
	}

	//void clear_color(colors::basic::color auto color) const
	//{
	//	NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
	//	//NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glClearColor(color.r, color.g, color.b, color.a));
	//}

	void set_viewport(::std::size_t x, ::std::size_t y, ::std::size_t width, ::std::size_t height) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
	}
};
namespace _detail
{
	template <auto Args>
	void derived_from_basic(const basic_framebuffer<Args>&);
}

template <class T>
concept framebuffer = requires(const T & obj) { _detail::derived_from_basic(obj); };

using default_framebuffer = basic_framebuffer<enums::framebuffer_target::framebuffer>;
using draw_framebuffer = basic_framebuffer<enums::framebuffer_target::draw>;
using read_framebuffer = basic_framebuffer<enums::framebuffer_target::read>;

NGS_LIB_MODULE_END