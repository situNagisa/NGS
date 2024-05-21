#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class>
	struct proxy;

	template<template<class...>class Template, class... Channels>
	struct proxy<Template<Channels...>>
	{
		constexpr static auto channel_layout()
		{
			return layout::structure(channels::bit_count<Channels>()...);
		}
		constexpr static ::std::size_t channel_count()
		{
			return sizeof...(Channels);
		}

		constexpr static ::std::size_t bit_count()
			requires (channels::arithmetic_channel<Channels> && ...)
		{
			return (channels::bit_count<Channels>() + ...);
		}

		constexpr static auto combinate(channels::underlying_type_t<Channels>... channel_value)
			requires ((channels::bit_count<Channels>() + ...) <= bits::algorithm::bit_of<::std::uint64_t>())
		{
			using result_type = byte_<bits::algorithm::bit_to_byte_ceil(bit_count())>;
			constexpr auto layout = channel_layout();
			return[=]<::std::size_t... Index>(::std::index_sequence<Index...>)
			{
				return result_type(((channels::bit_value<Channels>(channel_value) << layout[Index].second) | ...));
			}(::std::make_index_sequence<channel_count()>());
		}

		template<::std::size_t Index>
		using channel_type = ::std::tuple_element_t<Index, ::std::tuple<Channels...>>;
	};
}



template<color Color>
constexpr ::std::size_t channel_count()
{
	return _detail::proxy<type_traits::naked_t<color_channels_t<Color>>>::channel_count();
}

template<color Color, ::std::size_t Index>
	requires (Index < NGS_LIB_MODULE_NAME::channel_count<Color>())
using color_channel_at_t = typename _detail::proxy<type_traits::naked_t<color_channels_t<Color>>>::template channel_type<Index>;

template<arithmetic_color Color>
constexpr ::std::size_t bit_count()
{
	return _detail::proxy<type_traits::naked_t<color_channels_t<Color>>>::bit_count();
}

template<arithmetic_color Color, ::std::size_t Index>
	requires (NGS_LIB_MODULE_NAME::bit_count<Color>() <= bits::algorithm::bit_of<::std::uint64_t>()) && (Index < NGS_LIB_MODULE_NAME::channel_count<Color>())
constexpr auto channel(byte_<bits::algorithm::bit_to_byte_ceil(NGS_LIB_MODULE_NAME::bit_count<Color>())> value)
{
	using proxy_type = _detail::proxy<type_traits::naked_t<color_channels_t<Color>>>;
	using channel_type = typename proxy_type::template channel_type<Index>;
	constexpr auto channel_layout = proxy_type::channel_layout();
	auto [size, offset] = channel_layout[Index];

	return static_cast<channels::underlying_type_t<channel_type>>(bits::algorithm::extract(value, offset, size));
}

template<channels::arithmetic_channel... Channels>
	requires ((channels::bit_count<Channels>() + ...) <= bits::algorithm::bit_of<::std::uint64_t>())
constexpr auto combinate(channels::underlying_type_t<Channels>... channel_value)
{
	using proxy_type = _detail::proxy<::std::tuple<Channels...>>;
	return proxy_type::combinate(channel_value...);
}

NGS_LIB_MODULE_END