#pragma once

#include "./placeholder.h"
#include "./replace.h"
#include "./unpack.h"
#include "./packet.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<size_t... _FirstIndex, size_t... _SecondIndex>
	constexpr decltype(auto) apply(
		std::index_sequence<_FirstIndex...>,
		std::index_sequence<_SecondIndex...>,
		auto&& callable,
		auto&& first,
		auto&& second,
		auto&&... replace_params
	) requires (unpack_has_adl<decltype(first), _FirstIndex> && ...) && (unpack_has_adl<decltype(second), _SecondIndex> && ...)
	{
		return NGS_PP_PERFECT_FORWARD(callable)(
			NGS_LIB_NAME::replace(
				NGS_LIB_NAME::unpack<_FirstIndex>(NGS_PP_PERFECT_FORWARD(first)),
				NGS_PP_PERFECT_FORWARD(replace_params)...
			)...,
			NGS_LIB_NAME::replace(
				NGS_LIB_NAME::unpack<_SecondIndex>(NGS_PP_PERFECT_FORWARD(second)),
				NGS_PP_PERFECT_FORWARD(replace_params)...
			)...
			);
	}
}

inline constexpr struct {
	constexpr decltype(auto) operator()(auto&& callable, packet_like auto&& pack, auto&&... replace_params)const
	{
		return detail::apply(
			std::make_index_sequence<NGS_FUNCTIONAL_PARAMETER_PACKET_PACKET_NS::size_v<decltype(pack)>>(),
			std::make_index_sequence<0>(),
			NGS_PP_PERFECT_FORWARD(callable),
			NGS_PP_PERFECT_FORWARD(pack),
			packet<>{},
			NGS_PP_PERFECT_FORWARD(replace_params)...
		);
	}
}apply{};

inline constexpr struct {
	constexpr decltype(auto) operator()(auto&& callable, packet_like auto&& first, packet_like auto&& second, auto&&... replace_params)const
	{
		return detail::apply(
			std::make_index_sequence<NGS_FUNCTIONAL_PARAMETER_PACKET_PACKET_NS::size_v<decltype(first)>>(),
			std::make_index_sequence<NGS_FUNCTIONAL_PARAMETER_PACKET_PACKET_NS::size_v<decltype(second)>>(),
			NGS_PP_PERFECT_FORWARD(callable),
			NGS_PP_PERFECT_FORWARD(first),
			NGS_PP_PERFECT_FORWARD(second),
			NGS_PP_PERFECT_FORWARD(replace_params)...
		);
	}
}apply_pair{};

NGS_LIB_END