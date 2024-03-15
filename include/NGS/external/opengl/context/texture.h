#pragma once

#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto texture_creator()
	{
		basic::context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenTextures(1, &context));
		return context;
	}
	void texture_deleter(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteTextures(1, &context));
	}
	template<enums::texture_target Target>
	void texture_binder(basic::context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindTexture(static_cast<GLenum>(Target), context));
	}
}


NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(unknown_texture, _detail::texture_creator, _detail::texture_deleter);

template<enums::texture_target Target>
struct basic_texture : unknown_texture
{
	NGS_MPL_ENVIRON(basic_texture);
public:
	constexpr static auto target = Target;
	using machine_type = basic::context_machine<self_type, _detail::texture_binder<target>>;
};

using texture_1d = basic_texture<enums::texture_target::_1d>;
using texture_1d_array = basic_texture<enums::texture_target::_1d_array>;
using texture_2d = basic_texture<enums::texture_target::_2d>;
using texture_2d_array = basic_texture<enums::texture_target::_2d_array>;
using texture_3d = basic_texture<enums::texture_target::_3d>;
using texture_rectangle = basic_texture<enums::texture_target::rectangle>;

NGS_LIB_MODULE_END