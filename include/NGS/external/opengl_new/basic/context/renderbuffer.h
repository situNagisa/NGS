#pragma once

#include "../error.h"
#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


namespace _detail
{
	auto renderbuffer_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenRenderbuffers(1, &context));
		return context;
	}
	void renderbuffer_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteRenderbuffers(1, &context));
	}
	template<enums::renderbuffer_target Target>
	void renderbuffer_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindRenderbuffer(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_DEFINE_BASIC_CONTEXT(unknown_renderbuffer, _detail::renderbuffer_creator, _detail::renderbuffer_deleter);
}

template<enums::renderbuffer_target Target>
struct basic_renderbuffer : _detail::unknown_renderbuffer
{
	NGS_MPL_ENVIRON(basic_renderbuffer);
public:
	constexpr static auto target = Target;
	using machine_type = context_machine<self_type, _detail::renderbuffer_binder<target>>;

	void storage(enums::texture_internal_format format, ::std::size_t width, ::std::size_t height) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glRenderbufferStorage(
			static_cast<GLenum>(target),
			static_cast<GLenum>(format),
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		));
	}
};

using renderbuffer = basic_renderbuffer<enums::renderbuffer_target::renderbuffer>;

NGS_LIB_MODULE_END