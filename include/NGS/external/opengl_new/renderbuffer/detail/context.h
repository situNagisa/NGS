#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN


namespace _detail
{
	auto renderbuffer_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenRenderbuffers(1, &context));
		return context;
	}
	void renderbuffer_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteRenderbuffers(1, &context));
	}
	template<enums::renderbuffer_target Target>
	void renderbuffer_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBindRenderbuffer(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BASIC_CONTEXT(unknown_renderbuffer, _detail::renderbuffer_creator, _detail::renderbuffer_deleter);
}

template<enums::renderbuffer_target Target>
struct basic_renderbuffer : _detail::unknown_renderbuffer
{
	NGS_PP_INJECT(basic_renderbuffer);
public:
	constexpr static auto target = Target;
	using machine_type = contextes::context_machine<self_type, _detail::renderbuffer_binder<target>>;

	basic_renderbuffer(enums::texture_internal_format format, ::std::size_t width, ::std::size_t height)
	{
		contextes::bind(*this);
		self_type::storage(format, width, height);
	}

	void storage(enums::texture_internal_format format, ::std::size_t width, ::std::size_t height) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glRenderbufferStorage(
			::std::to_underlying(target),
			::std::to_underlying(format),
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		));
	}
};

namespace _detail
{
	template <auto Args>
	void derived_from_renderbuffer(const basic_renderbuffer<Args>&);
}

template <class T>
concept renderable = requires(const T & obj) { _detail::derived_from_renderbuffer(obj); };

using renderbuffer = basic_renderbuffer<enums::renderbuffer_target::renderbuffer>;

NGS_LIB_MODULE_END