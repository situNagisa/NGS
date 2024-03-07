#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct shader : basic::context
{
	NGS_MPL_ENVIRON(shader);
private:
	static auto _create()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateProgram());
		return context;
	}

public:
	struct machine_type : bases::singleton<machine_type>
	{
		using context_type = shader;

		void bind(const context_type& context) const
		{
			NGS_EXTERNAL_OPENGL_CHECK(::glUseProgram(context.get_context()));
		}
	};

	shader() noexcept : base_type(_create()) {}
	shader(self_type&&) = default;
	~shader()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteProgram(get_context()));
	}

	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteProgram(get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}
};



NGS_LIB_MODULE_END