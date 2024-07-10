#pragma once

#include "../enum.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::buffer_target Target>
void buffer_allocate(const contexts::buffer<Target>& buffer, size_t size, enums::usage usage)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(buffer);
	NGS_EXTERNAL_OPENGL_CHECK(glBufferData(static_cast<GLenum>(type_traits::object_t<decltype(buffer)>::target), size, nullptr, static_cast<GLenum>(usage)));
}

template<enums::buffer_target Target>
void buffer_describe(const contexts::buffer<Target>& buffer, const ::std::ranges::contiguous_range auto& data, enums::usage usage)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(buffer);
	constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
	NGS_EXTERNAL_OPENGL_CHECK(glBufferData(static_cast<GLenum>(type_traits::object_t<decltype(buffer)>::target), ::std::ranges::size(data) * value_size, ::std::ranges::data(data), static_cast<GLenum>(usage)));
}

template<enums::buffer_target Target>
void buffer_submit(const contexts::buffer<Target>& buffer, const ::std::ranges::contiguous_range auto& data, size_t offset = 0)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(buffer);
	constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
	NGS_EXTERNAL_OPENGL_CHECK(glBufferSubData(static_cast<GLenum>(type_traits::object_t<decltype(buffer)>::target), offset * value_size, ::std::ranges::size(data) * value_size, ::std::ranges::data(data)));
}

NGS_LIB_MODULE_END