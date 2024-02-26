#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Const, class To>
struct add_const_like
{
	using type = std::remove_const_t<To>;
};
template<class Const, class To>
using add_const_like_t = typename add_const_like<Const, To>::type;

template<class Const, class To>
struct add_const_like<const Const, To>
{
	using type = std::add_const_t<To>;
};

NGS_TYPE_TRAIT_END