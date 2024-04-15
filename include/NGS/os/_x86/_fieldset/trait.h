#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct underlying_type{};

template<class T> requires ::std::integral<T>
struct underlying_type<T> { using type = T; };

template<class T> requires requires{ typename type_traits::object_t<T>::underlying_type; }
struct underlying_type<T> { using type = typename type_traits::object_t<T>::underlying_type; };

template<class T>
using underlying_type_t = typename underlying_type<T>::type;


template<class>
struct creator : ::std::false_type {};

template<class T> requires ::std::integral<T>
struct creator<T> : ::std::true_type
{
	constexpr auto operator()(const T& value)const { return value; }
};

template<class T> requires requires(underlying_type_t<T> value){ { type_traits::object_t<T>::create(value) }; }
struct creator<T> : ::std::true_type
{
	constexpr auto operator()(const underlying_type_t<T>& value)const { return type_traits::object_t<T>::create(value); }
};

template<class T>
concept creatable = creator<T>::value;

template<class T>
inline constexpr creator<T> creator_v{};

NGS_LIB_MODULE_END
