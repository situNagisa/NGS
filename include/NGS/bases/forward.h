#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _Forward, class... _Bases>
struct base_forward : _Forward, _Bases...
{
	NGS_MPL_ENVIRON2(base_forward, _Forward);
public:
	using base_type::base_type;
	using base_type::operator=;
};

template<class _Forward, class... _ADLSet>
struct adl_forward : _Forward
{
	NGS_MPL_ENVIRON2(adl_forward, _Forward);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_END