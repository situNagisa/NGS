#pragma once

#include "../channel.h"
#include "./algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<channels::color_channel... Channels>
struct basic_color
{
	NGS_PP_INJECT_BEGIN(basic_color);
public:
	using channels_type = ::std::tuple<Channels...>;
};

template<channels::arithmetic_channel... Channels>
struct basic_arithmetic_color : basic_color<Channels...>
{
	NGS_PP_INJECT(basic_arithmetic_color);
public:

};

template<channels::arithmetic_channel... Channels>
	requires ((channels::bit_count<Channels>() + ...) <= bits::algorithm::bit_of<::std::uint64_t>())
struct fundamental_color : basic_arithmetic_color<Channels...>
{
	NGS_PP_INJECT_BEGIN(fundamental_color);
public:
	using value_type = byte_<bits::algorithm::bit_to_byte_ceil((channels::bit_count<Channels>() + ...))>;

	constexpr fundamental_color() = default;
	constexpr explicit(false) fundamental_color(value_type value) : _value(value) {}
	constexpr explicit(false) fundamental_color(channels::underlying_type_t<Channels>... channel_values)
		: _value(NGS_LIB_MODULE_NAME::combinate<Channels...>(channel_values...))
	{}

	constexpr auto&& value() { return _value; }
	constexpr auto&& value() const { return _value; }

	template<::std::size_t Index>
		requires (Index < sizeof...(Channels))
	constexpr decltype(auto) channel() const
	{
		return NGS_LIB_MODULE_NAME::channel<self_type, Index>(_value);
	}

	value_type _value;
};

namespace _detail
{
	template<template<class...>class, class T, ::std::size_t Size, class = ::std::make_index_sequence<Size>>
	struct constant_sequence;

	template<template<class...>class Container, class T, ::std::size_t Size, ::std::size_t... Index>
	struct constant_sequence<Container, T, Size, ::std::index_sequence<Index...>>
	{
		using type = Container<type_traits::index_type_identity_t<Index, T>...>;
	};

	template<channels::arithmetic_channel Color, ::std::size_t Size, class = ::std::make_index_sequence<Size>>
	struct array_color;

	template<channels::arithmetic_channel Color, ::std::size_t Size, ::std::size_t... Index>
	struct array_color<Color, Size, ::std::index_sequence<Index...>> : constant_sequence<basic_arithmetic_color, Color, Size>::type
	{
		NGS_PP_INJECT(array_color);
	public:
		constexpr array_color() = default;
		constexpr explicit(false) array_color(type_traits::index_type_identity_t<Index, channels::underlying_type_t<Color>>... channel_values)
			: _value{ channel_values... }
		{}

		constexpr auto&& value() { return _value; }
		constexpr auto&& value() const { return _value; }

		template<::std::size_t I>
			requires (I < Size)
		constexpr decltype(auto) channel() { return _value[I]; }
		template<::std::size_t I>
			requires (I < Size)
		constexpr decltype(auto) channel() const { return _value[I]; }

		::std::array<channels::underlying_type_t<Color>, Size> _value;
	};
}

template<channels::arithmetic_channel Color, ::std::size_t Size>
struct array_color : _detail::array_color<Color, Size>
{
	NGS_PP_INJECT(array_color);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END