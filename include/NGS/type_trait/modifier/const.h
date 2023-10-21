#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _From, class _To>
struct set_same_const
{
	using type = std::remove_const_t<_To>;
};
template<class _From, class _To>
using set_same_const_t = typename set_same_const<_From, _To>::type;

template<class _From, class _To>
struct set_same_const<const _From, _To>
{
	using type = std::add_const_t<_To>;
};

NGS_TYPE_TRAIT_END