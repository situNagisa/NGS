#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Reference, class _To>
struct add_reference_like
{
	using type = _To;
};
template<class _Reference, class _To>
using add_reference_like_t = typename add_reference_like<_Reference, _To>::type;

template<class _Reference, class _To>
struct add_reference_like<_Reference&, _To>
{
	using type = std::add_lvalue_reference_t<_To>;
};
template<class _Reference, class _To>
struct add_reference_like<_Reference&&, _To>
{
	using type = std::add_rvalue_reference_t<_To>;
};

NGS_TYPE_TRAIT_END