#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class Forward, class... Bases>
struct base_forward : Forward, Bases...
{
	NGS_MPL_ENVIRON2(base_forward, Forward);
public:
	using base_type::base_type;
	using base_type::operator=;
};

template<class Forward, class...>
struct adl_forward : Forward
{
	NGS_MPL_ENVIRON2(adl_forward, Forward);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_END