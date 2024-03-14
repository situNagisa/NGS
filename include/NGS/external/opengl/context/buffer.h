#pragma once

#include "../config.h"
#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct unknown_buffer : basic::context
{
	NGS_MPL_ENVIRON(unknown_buffer);
private:
	static auto _create()
	{
		basic::context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenBuffers(1, &context));
		return context;
	}
public:
	NGS_EXTERNAL_OPENGL_CONTEXT_TYPE_AUTO();

	unknown_buffer() noexcept : base_type(_create()) {}
	unknown_buffer(self_type&&) = default;
	~unknown_buffer()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteBuffers(1, &get_context()));
	}

	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteBuffers(1, &get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}
};

template<enums::buffer_target Target>
struct buffer : unknown_buffer
{
	NGS_MPL_ENVIRON(buffer);
public:
	constexpr static auto target = Target;

	struct machine_type : bases::singleton<machine_type>
	{
		using context_type = buffer;

		void bind(const context_type& context) const
		{
			NGS_EXTERNAL_OPENGL_CHECK(::glBindBuffer(static_cast<GLenum>(target), context.get_context()));
		}
	};

	using base_type::base_type;
	using base_type::operator=;
};



NGS_LIB_MODULE_END