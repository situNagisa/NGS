#pragma once

#include "../replace.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<packet_like, class...>
struct meta_actual_packet;

template<template<class...>class _Packet, class... _Params, class... _Args>
struct meta_actual_packet<_Packet<_Params...>, _Args...> {
	using type = _Packet<meta_replace_t<_Params, _Args...>...>;
};

template<packet_like _Packet, class... _Args>
using meta_actual_packet_t = typename meta_actual_packet<_Packet, _Args...>::type;

NGS_LIB_MODULE_END