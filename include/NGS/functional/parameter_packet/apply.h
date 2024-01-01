#pragma once

#include "./placeholder.h"
#include "./replace.h"
#include "./unpack.h"
#include "./packet.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<size_t... _Index>
	constexpr decltype(auto) apply(
		std::index_sequence<_Index...>,
		auto&& callable,
		auto&& packet,
		auto&&... replace_params
	) requires (unpack_has_adl<decltype(packet), _Index> && ...)
	{
		return NGS_PP_PERFECT_FORWARD(callable)(
			NGS_LIB_NAME::replace(
				NGS_LIB_NAME::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packet)),
				NGS_PP_PERFECT_FORWARD(replace_params)...
			)...
			);
	}
}

constexpr decltype(auto) apply(auto&& callable, packet_like auto&& packet, auto&&... replace_params)
{
	return detail::apply(
		std::make_index_sequence<NGS_FUNCTIONAL_PARAMETER_PACKET_PACKET_NS::size_v<decltype(packet)>>(),
		NGS_PP_PERFECT_FORWARD(callable),
		NGS_PP_PERFECT_FORWARD(packet),
		NGS_PP_PERFECT_FORWARD(replace_params)...
	);
}

NGS_LIB_END