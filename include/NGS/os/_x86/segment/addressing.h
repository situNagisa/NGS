#pragma once

#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto addressing_real(::std::uint16_t visual, ::std::uint16_t ds)
{
	return static_cast<pointer_t>(ds) << 4 | visual;
}

constexpr bool addressable(pointer_t visual, const descriptor& descriptor)
{
	return descriptor.present &&  visual < descriptor.segment_size();
}

constexpr pointer_t addressing_protected(pointer_t visual, const descriptor& descriptor)
{
	return descriptor.base_address + visual;
}

NGS_LIB_MODULE_END