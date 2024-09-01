#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Reference, class To>
struct add_reference_like
{
	using type = To;
};
template<class Reference, class To>
using add_reference_like_t = typename add_reference_like<Reference, To>::type;

template<class Reference, class To>
struct add_reference_like<Reference&, To>
{
	using type = std::add_lvalue_reference_t<To>;
};
template<class Reference, class To>
struct add_reference_like<Reference&&, To>
{
	using type = std::add_rvalue_reference_t<To>;
};

NGS_TYPE_TRAIT_END