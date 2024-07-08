#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using rank_t = ::std::size_t;

template<class T>
struct rank { consteval static rank_t value() { return 0; } };
template<class T>
	requires ::std::is_object_v<T> && requires{ { T::rank() } -> ::std::convertible_to<rank_t>; }
struct rank<T> { consteval static rank_t value() { return static_cast<rank_t>(T::rank()); } };


template<class T>
struct rank_dynamic { consteval static rank_t value() { return 0; } };
template<class T>
	requires ::std::is_object_v<T>&& requires{ { T::rank_dynamic() } -> ::std::convertible_to<rank_t>; }
struct rank_dynamic<T> { consteval static rank_t value() { return static_cast<rank_t>(T::rank_dynamic()); } };


template<class T>
struct rank_adaptor { consteval static rank_t value() { return 0; } };
template<class T>
	requires ::std::is_object_v<T>&& requires{ { T::rank_adaptor() } -> ::std::convertible_to<rank_t>; }
struct rank_adaptor<T> { consteval static rank_t value() { return static_cast<rank_t>(T::rank_adaptor()); } };


NGS_LIB_MODULE_END