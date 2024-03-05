#pragma once

#include "../enum.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

void allocate(const unknown_buffer& buffer, enums::buffer_target target, size_t size, enums::usage usage)
{
	NGS_EXTERNAL_OPENGL_CHECK(glBufferData(static_cast<GLenum>(target), size, nullptr, static_cast<GLenum>(usage)));
}

template<enums::buffer_target _Target>
void allocate(const buffer<_Target>& buffer, size_t size, enums::usage usage)
{
	NGS_LIB_MODULE_NAME::allocate(buffer, type_traits::object_t<decltype(buffer)>::target, size, usage);
}

void describe(const unknown_buffer& buffer, enums::buffer_target target, const ::std::ranges::contiguous_range auto& data, enums::usage usage)
{
	constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
	NGS_EXTERNAL_OPENGL_CHECK(glBufferData(static_cast<GLenum>(target), ::std::ranges::size(data) * value_size, ::std::ranges::data(data), static_cast<GLenum>(usage)));
}

template<enums::buffer_target _Target>
void describe(const buffer<_Target>& buffer, const ::std::ranges::contiguous_range auto& data, enums::usage usage)
{
	NGS_LIB_MODULE_NAME::describe(buffer, type_traits::object_t<decltype(buffer)>::target, data, usage);
}

void submit(const unknown_buffer& buffer, enums::buffer_target target, const ::std::ranges::contiguous_range auto& data, size_t offset = 0)
{
	constexpr auto value_size = sizeof(::std::ranges::range_value_t<decltype(data)>);
	NGS_EXTERNAL_OPENGL_CHECK(glBufferSubData(static_cast<GLenum>(target), offset * value_size, ::std::ranges::size(data) * value_size, ::std::ranges::data(data)));
}

template<enums::buffer_target _Target>
void submit(const buffer<_Target>& buffer, const ::std::ranges::contiguous_range auto& data, size_t offset = 0)
{
	NGS_LIB_MODULE_NAME::submit(buffer, type_traits::object_t<decltype(buffer)>::target, data, offset);
}

NGS_LIB_MODULE_END