#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<size_t _Index>
constexpr decltype(auto) unpack(is_packer auto&& pack)
{
	return pack.template get<_Index>();
}

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(unpack);