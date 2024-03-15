#pragma once

#include "../config.h"
#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto buffer_creator()
	{
		basic::context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenBuffers(1, &context));
		return context;
	}
	void buffer_deleter(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteBuffers(1, &context));
	}
	template<enums::buffer_target Target>
	void buffer_binder(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindBuffer(static_cast<GLenum>(Target), context));
	}
}

NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(unknown_buffer, _detail::buffer_creator, _detail::buffer_deleter);

template<enums::buffer_target Target>
struct buffer : unknown_buffer
{
	NGS_MPL_ENVIRON(buffer);
public:
	constexpr static auto target = Target;
	using machine_type = basic::context_machine<self_type, _detail::buffer_binder<target>>;
};



NGS_LIB_MODULE_END