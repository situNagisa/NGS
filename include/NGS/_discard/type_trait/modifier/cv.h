#pragma once

#include "./const.h"
#include "./volatile.h"

NGS_TYPE_TRAIT_BEGIN

template<class CV, class To>
struct add_cv_like
{
	using type = std::remove_cv_t<To>;
};
template<class CV, class To>
using add_cv_like_t = typename add_cv_like<CV, To>::type;

template<class CV, class To>
struct add_cv_like<const CV, To>
{
	using type = std::add_const_t<std::remove_cv_t<To>>;
};
template<class CV, class To>
struct add_cv_like<volatile CV, To>
{
	using type = std::add_volatile_t<std::remove_cv_t<To>>;
};
template<class CV, class To>
struct add_cv_like<const volatile CV, To>
{
	using type = std::add_cv_t<To>;
};

NGS_TYPE_TRAIT_END