#pragma once

#include "./concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template<size_t _Index>
constexpr decltype(auto) unpack(is_packer auto&& pack)
	requires requires { pack.template get<_Index>(); }
{
	return pack.template get<_Index>();
}

NGS_STATIC_FUNCTIONAL_END