#pragma once

#include "./const.h"
#include "./volatile.h"

NGS_TYPE_TRAIT_BEGIN

template<class _From, class _To>
struct set_same_cv
{
	using type = std::remove_cv_t<_To>;
};
template<class _From, class _To>
using set_same_cv_t = typename set_same_cv<_From, _To>::type;

template<class _From,class _To>
struct set_same_cv<const _From, _To>
{
	using type = std::add_const_t<std::remove_cv_t<_To>>;
};
template<class _From, class _To>
struct set_same_cv<volatile _From, _To>
{
	using type = std::add_volatile_t<std::remove_cv_t<_To>>;
};
template<class _From, class _To>
struct set_same_cv<const volatile _From, _To>
{
	using type = std::add_cv_t<_To>;
};

NGS_TYPE_TRAIT_END