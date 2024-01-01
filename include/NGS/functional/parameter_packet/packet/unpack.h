#pragma once

#include "./packet.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<size_t _Index>
constexpr decltype(auto) unpack(packet_like auto&& pack)
{
	return statics::tuples::get<_Index>(NGS_PP_PERFECT_FORWARD(pack));
}

template<size_t _Index, packet_like _StoragePacket> requires requires{typename type_traits::object_t<_StoragePacket>::parameters_type; }
constexpr decltype(auto) unpack(_StoragePacket&& pack)
{
	using parameters_type = typename type_traits::object_t<_StoragePacket>::parameters_type;
	return type_traits::restore<element_t<_Index, parameters_type>>(statics::tuples::get<_Index>(NGS_PP_PERFECT_FORWARD(pack)));
}

NGS_LIB_MODULE_END