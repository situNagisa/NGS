#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<arithmetic_channel Channel>
constexpr auto bit_value(underlying_type_t<Channel> v)
{
	if constexpr (sizeof(underlying_type_t<Channel>) == NGS_LIB_MODULE_NAME::bit_count<Channel>())
	{
		return v;
	}
	else
	{
		constexpr auto count = NGS_LIB_MODULE_NAME::bit_count<Channel>();
		return v & bits::algorithm::mask(count);
	}
}

template<arithmetic_channel Channel,::std::floating_point Result = float>
constexpr auto normalize(underlying_type_t<Channel> v)
{
	constexpr auto count = NGS_LIB_MODULE_NAME::bit_count<Channel>();
	constexpr auto max = bits::algorithm::mask(count);

	if constexpr (!max)
	{
		return static_cast<Result>(0);
	}
	else
	{
		return static_cast<Result>(NGS_LIB_MODULE_NAME::bit_value<Channel>(v)) / static_cast<Result>(max);
	}
}

template<arithmetic_channel From, arithmetic_channel To>
constexpr auto convert(underlying_type_t<From> from)
{
	constexpr auto from_count = NGS_LIB_MODULE_NAME::bit_count<From>();
	constexpr auto to_count = NGS_LIB_MODULE_NAME::bit_count<To>();

	if constexpr(!from_count || !to_count)
	{
		return underlying_type_t<To>(0);
	}
	else
	{
		constexpr auto from_max = bits::algorithm::mask(from_count);
		constexpr auto to_max = bits::algorithm::mask(to_count);

		constexpr auto value = NGS_LIB_MODULE_NAME::bit_value<From>(from);
		constexpr auto result = value * to_max / from_max;

		return result;
	}
}

NGS_LIB_MODULE_END