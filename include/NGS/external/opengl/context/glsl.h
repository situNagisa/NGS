#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct basic_glsl : basic::context
{
	NGS_MPL_ENVIRON(basic_glsl);
private:
	static auto _create(enums::shader_type target)
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateShader(static_cast<::GLenum>(target)));
		return context;
	}
public:
	basic_glsl(enums::shader_type target) noexcept : base_type(_create(target)) {}
	basic_glsl(self_type&&) = default;
	~basic_glsl()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteShader(get_context()));
	}

	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteShader(get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}
};

template<enums::shader_type Target>
struct glsl : basic_glsl
{
	NGS_MPL_ENVIRON(glsl);
public:
	constexpr static auto target = Target;

	glsl() : base_type(target) {}
	glsl(self_type&&) = default;
	using base_type::operator=;
};



NGS_LIB_MODULE_END