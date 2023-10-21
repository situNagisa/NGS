#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _From, class _To>
struct set_same_volatile
{
	using type = std::remove_volatile_t<_To>;
};
template<class _From, class _To>
using set_same_volatile_t = typename set_same_volatile<_From, _To>::type;

template<class _From, class _To>
struct set_same_volatile<const _From, _To>
{
	using type = std::add_volatile_t<_To>;
};


NGS_TYPE_TRAIT_END