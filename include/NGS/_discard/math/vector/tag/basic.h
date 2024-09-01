#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct vector {};

template<class> struct trait { using type = void; };

template<class _T> using trait_t = typename trait<_T>::type;

template<class _T> requires requires { typename type_traits::object_t<_T>::linear_algebra_category_type; }
struct trait<_T> { using type = typename type_traits::object_t<_T>::linear_algebra_category_type; };

template<class _Tag>
struct tag { using linear_algebra_category_type = _Tag; };

NGS_LIB_MODULE_END