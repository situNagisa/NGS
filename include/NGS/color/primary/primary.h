#pragma once

#include "../channel.h"
#include "../basic.h"
#include "./channel.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<channels::arithmetic_channel... Channels>
	struct primary;

	template<class... Channels>
	concept fundamental_value = (::std::has_single_bit((channels::bit_count<Channels>() + ...))) && ((channels::bit_count<Channels>() + ...) <= bits::algorithm::bit_of<::std::uint64_t>());

	template<channels::arithmetic_channel... Channels>
		requires fundamental_value<Channels...>
	struct primary<Channels...> : basic::fundamental_color<Channels...>
	{
		NGS_PP_INJECT(primary);
	public:
		using base_type::base_type;
		using base_type::operator=;
	};

	template<channels::arithmetic_channel First, channels::arithmetic_channel... Channels>
		requires !fundamental_value<First,Channels...> && (channels::arithmetic_channel_equivalence<First, Channels> && ...)
	struct primary<First, Channels...> : basic::array_color<First, 1 + sizeof...(Channels)>
	{
		NGS_PP_INJECT(primary);
	public:
		using base_type::base_type;
		using base_type::operator=;
	};

	template<template<class...>class FindChannel, primary_channel... Channels>
	struct index_of
	{
		constexpr static auto value()
		{
			return []<::std::size_t... Index>(::std::index_sequence<Index...>)
			{
				return ((cpt::derived_from_specialization<Channels,FindChannel> ? Index : 0) + ...);
			}(::std::make_index_sequence<sizeof...(Channels)>());
		}
	};
}



template<primary_channel C0, primary_channel C1, primary_channel C2, primary_channel C3>
	requires _detail::full_primary_channel<C0,C1,C2,C3>
struct primary : basic::basic_arithmetic_color<C0, C1, C2, C3>
{
	NGS_PP_INJECT(primary);
public:

	constexpr primary() = default;
	constexpr explicit(false) primary(channels::underlying_type_t<C0> c0, channels::underlying_type_t<C1> c1, channels::underlying_type_t<C2> c2, channels::underlying_type_t<C3> c3)
		: _value(c0, c1, c2, c3)
	{}

	template<::std::size_t I>
		requires (I < 4)
	constexpr decltype(auto) channel() { return _value.template channel<I>(); }
	template<::std::size_t I>
		requires (I < 4)
	constexpr decltype(auto) channel() const { return _value.template channel<I>(); }

	constexpr decltype(auto) alpha() { return self_type::template channel<_detail::index_of<alpha_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) alpha() const { return self_type::template channel<_detail::index_of<alpha_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) red() { return self_type::template channel<_detail::index_of<red_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) red() const { return self_type::template channel<_detail::index_of<red_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) green() { return self_type::template channel<_detail::index_of<green_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) green() const { return self_type::template channel<_detail::index_of<green_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) blue() { return self_type::template channel<_detail::index_of<blue_channel, C0, C1, C2, C3>::value()>(); }
	constexpr decltype(auto) blue() const { return self_type::template channel<_detail::index_of<blue_channel, C0, C1, C2, C3>::value()>(); }

	_detail::primary<C0, C1, C2, C3> _value{};
};

NGS_LIB_MODULE_END