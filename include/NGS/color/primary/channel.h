#pragma once

#include "../channel.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<ccpt::uint BitCount>
struct alpha_channel : channels::channel<BitCount::value>
{
	constexpr static auto _value = 1u << 0;
};

template<ccpt::uint BitCount>
struct red_channel : channels::channel<BitCount::value>
{
	constexpr static auto _value = 1u << 1;
};

template<ccpt::uint BitCount>
struct green_channel : channels::channel<BitCount::value>
{
	constexpr static auto _value = 1u << 2;
};

template<ccpt::uint BitCount>
struct blue_channel : channels::channel<BitCount::value>
{
	constexpr static auto _value = 1u << 3;
};

template<class T>
concept primary_channel = channels::arithmetic_channel<T>
	&& (cpt::derived_from_specialization<T, alpha_channel> 
	|| cpt::derived_from_specialization<T, red_channel>
	|| cpt::derived_from_specialization<T, green_channel>
	|| cpt::derived_from_specialization<T, blue_channel>
		);

namespace _detail
{
	template<class... Channels>
	concept full_primary_channel = (primary_channel<Channels> && ...) && ((type_traits::object_t<Channels>::_value | ...) == 0b1111);
}

template<::std::size_t BitCount>
using alpha_c = alpha_channel<::std::integral_constant<::std::size_t, BitCount>>;

template<::std::size_t BitCount>
using red_c = red_channel<::std::integral_constant<::std::size_t, BitCount>>;

template<::std::size_t BitCount>
using green_c = green_channel<::std::integral_constant<::std::size_t, BitCount>>;

template<::std::size_t BitCount>
using blue_c = blue_channel<::std::integral_constant<::std::size_t, BitCount>>;

NGS_LIB_MODULE_END