#pragma once

#include "./packet.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<size_t Index>
constexpr decltype(auto) unpack(packet_like auto&& pack)
{
	return statics::tuples::get<Index>(NGS_PP_PERFECT_FORWARD(pack));
}

template<size_t Index, packet_like StoragePacket> requires requires{typename type_traits::object_t<StoragePacket>::parameters_type; }
constexpr decltype(auto) unpack(StoragePacket&& pack)
{
	using parameters_type = typename type_traits::object_t<StoragePacket>::parameters_type;
	return type_traits::restore<element_t<Index, parameters_type>>(statics::tuples::get<Index>(NGS_PP_PERFECT_FORWARD(pack)));
}

NGS_LIB_MODULE_END