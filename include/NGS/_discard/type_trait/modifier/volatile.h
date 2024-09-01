#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Volatile, class To>
struct add_volatile_like
{
	using type = std::remove_volatile_t<To>;
};
template<class Volatile, class To>
using add_volatile_like_t = typename add_volatile_like<Volatile, To>::type;

template<class Volatile, class To>
struct add_volatile_like<const Volatile, To>
{
	using type = std::add_volatile_t<To>;
};


NGS_TYPE_TRAIT_END