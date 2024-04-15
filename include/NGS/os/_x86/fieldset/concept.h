#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<::std::integral T, ::std::size_t N>
	constexpr void derived_from_stl_array(const ::std::array<T, N>&);

	template<class T>
	concept stl_array = requires(T t) { _detail::derived_from_stl_array(t); };
}

template<class T>
concept fieldset_descriptor = bits::bitsets::bit_integral<underlying_type_t<T>> && _detail::stl_array<decltype(NGS_LIB_MODULE_NAME::field_v<T>())>;

template<class T>
concept fieldset = bits::bitsets::bitset<T> && fieldset_descriptor<T>;

NGS_LIB_MODULE_END