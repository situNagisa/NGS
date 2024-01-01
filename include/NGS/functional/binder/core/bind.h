#pragma once

#include "./binder.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto bind(auto&& functor, parameter_packet::packet_like auto&& packet)
{
	return binder<decltype(functor), decltype(packet)>(NGS_PP_PERFECT_FORWARD(functor), NGS_PP_PERFECT_FORWARD(packet));
}

constexpr auto bind(auto&& functor, auto&&... args)
{
	return NGS_LIB_MODULE_NAME::bind(NGS_PP_PERFECT_FORWARD(functor), parameter_packet::make_packet(NGS_PP_PERFECT_FORWARD(args)...));
}

namespace _detail
{
	template<size_t _Offset, size_t... _Index>
	constexpr decltype(auto) bind_on_sequence(::std::index_sequence<_Index...>, auto&& functor, auto&&... args)
	{
		return NGS_LIB_MODULE_NAME::bind(NGS_PP_PERFECT_FORWARD(functor), NGS_PP_PERFECT_FORWARD(args)..., parameter_packet::placeholders::n<_Index + _Offset + 1>...);
	}
}

template<size_t _Sequence, size_t _Offset = 0>
constexpr decltype(auto) bind(auto&& functor, auto&&... args)
{
	return _detail::bind_on_sequence<_Offset>(::std::make_index_sequence<_Sequence>(), NGS_PP_PERFECT_FORWARD(functor), NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END
