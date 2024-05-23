#pragma once

#include "../concept.h"
#include "./bit_byte.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
constexpr ::std::size_t byte_of() noexcept { return sizeof(type_traits::object_t<T>); }

template<class T>
constexpr ::std::size_t bit_of() noexcept { return NGS_LIB_MODULE_NAME::byte_to_bit(NGS_LIB_MODULE_NAME::byte_of<T>()); }

template<class T>
	requires concepts::static_sized_range<T> || concepts::bit_operatable<T>
consteval auto static_size()
{
	if constexpr(concepts::static_sized_range<T>)
	{
		return external::stl::ranges::algorithm::static_size<T>();
	}
	else if constexpr(concepts::bit_operatable<T>)
	{
		return NGS_LIB_MODULE_NAME::bit_of<T>();
	}

}

NGS_LIB_MODULE_END