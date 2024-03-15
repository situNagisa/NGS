#pragma once

#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


namespace _detail
{
	auto renderbuffer_creator()
	{
		basic::context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenRenderbuffers(1, &context));
		return context;
	}
	void renderbuffer_deleter(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteRenderbuffers(1, &context));
	}
	template<enums::framebuffer_target Target>
	void renderbuffer_binder(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindRenderbuffer(static_cast<GLenum>(Target), context));
	}
}


NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(unknown_renderbuffer, _detail::renderbuffer_creator, _detail::renderbuffer_deleter);

template<enums::renderbuffer_target Target>
struct basic_renderbuffer : unknown_renderbuffer
{
	NGS_MPL_ENVIRON(basic_renderbuffer);
public:
	constexpr static auto target = Target;
	using machine_type = basic::context_machine<self_type, _detail::renderbuffer_binder<target>>;
};

using renderbuffer = basic_renderbuffer<enums::renderbuffer_target::renderbuffer>;

NGS_LIB_MODULE_END