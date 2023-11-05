#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Volatile, class _To>
struct add_volatile_like
{
	using type = std::remove_volatile_t<_To>;
};
template<class _Volatile, class _To>
using add_volatile_like_t = typename add_volatile_like<_Volatile, _To>::type;

template<class _Volatile, class _To>
struct add_volatile_like<const _Volatile, _To>
{
	using type = std::add_volatile_t<_To>;
};


NGS_TYPE_TRAIT_END