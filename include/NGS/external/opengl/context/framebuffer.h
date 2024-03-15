#pragma once

#include "../config.h"
#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto framebuffer_creator()
	{
		basic::context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenFramebuffers(1, &context));
		return context;
	}
	void framebuffer_deleter(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteFramebuffers(1, &context));
	}
	template<enums::framebuffer_target Target>
	void framebuffer_binder(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindFramebuffer(static_cast<GLenum>(Target), context));
	}
}


NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(unknown_framebuffer, _detail::framebuffer_creator, _detail::framebuffer_deleter);

template<enums::framebuffer_target Target>
struct basic_framebuffer : unknown_framebuffer
{
	NGS_MPL_ENVIRON(basic_framebuffer);
public:
	constexpr static auto target = Target;
	using machine_type = basic::context_machine<self_type, _detail::framebuffer_binder<target>>;
};

using framebuffer = basic_framebuffer<enums::framebuffer_target::framebuffer>;
using draw_framebuffer = basic_framebuffer<enums::framebuffer_target::draw>;
using read_framebuffer = basic_framebuffer<enums::framebuffer_target::read>;

NGS_LIB_MODULE_END