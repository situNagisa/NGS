#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class Modifier>
using add_const_like_t = ::std::conditional_t<::std::is_const_v<Modifier>, ::std::add_const_t<T>, ::std::remove_const_t<T>>;

template<class T, class Modifier>
using add_volatile_like_t = ::std::conditional_t<::std::is_volatile_v<Modifier>, ::std::add_volatile_t<T>, ::std::remove_volatile_t<T>>;

template<class T, class Modifier>
using add_reference_like_t = ::std::conditional_t<
	::std::is_reference_v<Modifier>,
	::std::conditional_t<::std::is_lvalue_reference_v<Modifier>, ::std::add_lvalue_reference_t<T>, ::std::add_rvalue_reference_t<T>>,
	::std::remove_reference_t<T>
>;

template<class T, class Modifier>
using add_pointer_like_t = ::std::conditional_t<::std::is_pointer_v<Modifier>, ::std::add_pointer_t<T>, ::std::remove_pointer_t<T>>;

template<class T, class Modifier>
using add_cv_like_t = add_const_like_t<add_volatile_like_t<T, Modifier>, Modifier>;

template<class T, class Modifier>
using add_cvref_like_t = add_reference_like_t<add_cv_like_t<T, Modifier>, Modifier>;

NGS_LIB_MODULE_END