#pragma once

#include "../config.h"
#include "../basic.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vertex_array : basic::context
{
	NGS_MPL_ENVIRON(vertex_array);
public:
	NGS_EXTERNAL_OPENGL_CONTEXT_TYPE_AUTO();
	struct machine_type : bases::singleton<machine_type>
	{
		using context_type = vertex_array;

		void bind(const context_type& context) const
		{
			NGS_EXTERNAL_OPENGL_CHECK(::glBindVertexArray(context.get_context()));
		}
	};
private:
	static auto _create()
	{
		basic::context_t vertex_array;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenVertexArrays(1, &vertex_array));
		return vertex_array;
	
	}
public:
	vertex_array(): base_type(_create()) {}
	~vertex_array()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteVertexArrays(1, &get_context()));
	}
	vertex_array(self_type&&) = default;
	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteVertexArrays(1, &get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}
};

NGS_LIB_MODULE_END