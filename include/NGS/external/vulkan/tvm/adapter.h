#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
struct adapter
{
	using type = _T;
};

template<cpt::fundamental _T> requires !::std::ranges::contiguous_range<_T>
struct adapter<_T>
{
	using type = _T;
};

template<std::ranges::contiguous_range _Range>
struct adapter<_Range>
{
	using range_type = _Range;
	using value_type = type_traits::naked_t<std::ranges::range_value_t<_Range>>;
	using type = value_type[sizeof(_Range) / sizeof(value_type)];
};

template<class _T>
using adapter_t = typename adapter<_T>::type;


NGS_LIB_MODULE_END