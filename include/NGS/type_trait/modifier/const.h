#pragma once

#include "../defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Const, class _To>
struct add_const_like
{
	using type = std::remove_const_t<_To>;
};
template<class _Const, class _To>
using add_const_like_t = typename add_const_like<_Const, _To>::type;

template<class _Const, class _To>
struct add_const_like<const _Const, _To>
{
	using type = std::add_const_t<_To>;
};

NGS_TYPE_TRAIT_END