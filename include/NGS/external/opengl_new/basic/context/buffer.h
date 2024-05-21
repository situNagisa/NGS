#pragma once

#include "../config.h"
#include "../enum.h"
#include "../error.h"
#include "./basic.h"
#include "./bind.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto buffer_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenBuffers(1, &context));
		return context;
	}
	void buffer_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteBuffers(1, &context));
	}
	template<enums::buffer_target Target>
	void buffer_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindBuffer(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_DEFINE_BASIC_CONTEXT(unknown_buffer, _detail::buffer_creator, _detail::buffer_deleter);
}

template<enums::buffer_target Target>
struct buffer : _detail::unknown_buffer
{
	NGS_PP_INJECT(buffer);
public:
	constexpr static auto target = Target;
	using machine_type = context_machine<self_type, _detail::buffer_binder<target>>;

	using base_type::base_type;
	using base_type::operator=;
	buffer(self_type&&) = default;
	self_type& operator=(self_type&&) = default;
	~buffer()
	{
#if defined(NGS_EXTERNAL_OPENGL_CHECK_BIND)
		if (_detail::is_binding(*this))
			_detail::unbind(*this);
#endif
	}

	void allocate(size_t size, enums::usage usage) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glBufferData(static_cast<GLenum>(target), size, nullptr, static_cast<GLenum>(usage)));
	}

	void describe(const ::std::ranges::contiguous_range auto& data, enums::usage usage) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
		NGS_EXTERNAL_OPENGL_CHECK(::glBufferData(static_cast<GLenum>(target), ::std::ranges::size(data) * value_size, ::std::ranges::data(data), static_cast<GLenum>(usage)));
	}

	void submit(const ::std::ranges::contiguous_range auto& data, size_t offset = 0) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
		NGS_EXTERNAL_OPENGL_CHECK(::glBufferSubData(static_cast<GLenum>(target), offset * value_size, ::std::ranges::size(data) * value_size, ::std::ranges::data(data)));
	}
};

using vertex_buffer = buffer<enums::buffer_target::array>;
using indices_buffer = buffer<enums::buffer_target::element>;
using uniform_buffer = buffer<enums::buffer_target::uniform>;

NGS_LIB_MODULE_END