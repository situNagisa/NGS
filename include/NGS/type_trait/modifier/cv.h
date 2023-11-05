#pragma once

#include "./const.h"
#include "./volatile.h"

NGS_TYPE_TRAIT_BEGIN

template<class _CV, class _To>
struct add_cv_like
{
	using type = std::remove_cv_t<_To>;
};
template<class _CV, class _To>
using add_cv_like_t = typename add_cv_like<_CV, _To>::type;

template<class _CV, class _To>
struct add_cv_like<const _CV, _To>
{
	using type = std::add_const_t<std::remove_cv_t<_To>>;
};
template<class _CV, class _To>
struct add_cv_like<volatile _CV, _To>
{
	using type = std::add_volatile_t<std::remove_cv_t<_To>>;
};
template<class _CV, class _To>
struct add_cv_like<const volatile _CV, _To>
{
	using type = std::add_cv_t<_To>;
};

NGS_TYPE_TRAIT_END