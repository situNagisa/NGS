#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct register_bit{};


template<class T> requires requires { { type_traits::object_t<T>::bit_size() } -> ::std::convertible_to<::std::size_t>; }
struct register_bit<T>
{
	constexpr static auto value() { return type_traits::object_t<T>::bit_size(); }
};

template<class T>
constexpr ::std::size_t register_bit_v() { return static_cast<::std::size_t>(register_bit<T>::value()); }

template<class>
struct register_category
{
	using type = void;
};


template<class T> requires requires { typename type_traits::object_t<T>::register_category_type; }
struct register_category<T>
{
	using type = typename type_traits::object_t<T>::register_category_type;
};

template<class T>
using register_category_t = typename register_category<T>::type;

NGS_LIB_MODULE_END