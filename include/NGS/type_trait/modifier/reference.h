#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _From,class _To>
struct set_same_reference
{
	using type = _To;
};
template<class _From, class _To>
using set_same_reference_t = typename set_same_reference<_From, _To>::type;

template<class _From,class _To>
struct set_same_reference<_From&, _To>
{
	using type = std::add_lvalue_reference_t<_To>;
};
template<class _From, class _To>
struct set_same_reference<_From&&, _To>
{
	using type = std::add_rvalue_reference_t<_To>;
};

NGS_TYPE_TRAIT_END