#pragma once

#include "./placeholder.h"
#include "./replace.h"
#include "./unpack.h"
#include "./packet.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<class, class, class...> struct apply_result;
	template<class _Callable, class _Packet, class... _Args>
	using apply_result_t = typename apply_result<_Callable, _Packet, _Args...>::type;

	template<class _Callable, template<class...>class _Packet, class... _Params>
	struct apply_result<_Callable, _Packet<_Params...>>
	{
		using type = ::std::invoke_result_t<_Callable, _Params...>;
	};

	template<class _Callable, template<class...>class _Packet, class... _Params, class... _Args>
	struct apply_result<_Callable, _Packet<_Params...>, _Args...>
	{
		using type = apply_result_t<_Callable, packets::meta_actual_packet_t<_Packet<_Params...>, _Args...>>;
	};
}

template<class _Callable, packet_like _Packet, class... _Args>
using apply_result_t = detail::apply_result_t<_Callable, type_traits::naked_t<_Packet>, _Args...>;

namespace detail
{
	template<size_t... _FirstIndex, size_t... _SecondIndex, class _Callable, class _FirstPacket, class _SecondPacket, class... _Args>
	constexpr NGS_LIB_NAME::apply_result_t<_Callable&&, statics::tuples::meta_cat_t<_FirstPacket&&, _SecondPacket&&>, _Args&&...>
		apply(
			std::index_sequence<_FirstIndex...>,
			std::index_sequence<_SecondIndex...>,
			_Callable&& callable,
			_FirstPacket&& first,
			_SecondPacket&& second,
			_Args&&... replace_params
		)
		requires (unpack_has_adl<_FirstPacket&&, _FirstIndex> && ...) && (unpack_has_adl<_SecondPacket&&, _SecondIndex> && ...)
	{
		using result_type = decltype(NGS_PP_PERFECT_FORWARD(callable)(
			NGS_LIB_NAME::replace(
				NGS_LIB_NAME::unpack<_FirstIndex>(NGS_PP_PERFECT_FORWARD(first)),
				NGS_PP_PERFECT_FORWARD(replace_params)...
			)...,
			NGS_LIB_NAME::replace(
				NGS_LIB_NAME::unpack<_SecondIndex>(NGS_PP_PERFECT_FORWARD(second)),
				NGS_PP_PERFECT_FORWARD(replace_params)...
			)...
			));
		static_assert(::std::same_as< NGS_LIB_NAME::apply_result_t<_Callable&&, statics::tuples::meta_cat_t<_FirstPacket&&, _SecondPacket&&>, _Args&&...>, result_type>);
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