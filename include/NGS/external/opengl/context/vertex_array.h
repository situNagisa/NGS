#pragma once

#include "../basic.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vertex_array : basic::context
{
	NGS_MPL_ENVIRON(vertex_array);
public:

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
		context_t vertex_array;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenVertexArrays(1, &vertex_array));
		return vertex_array;
	
	}
public:
	vertex_array(): base_type(_create()) {}
	~vertex_array()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteVertexArrays(1, &get_context()));
	}
};

NGS_LIB_MODULE_END