#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class T, class... Types>
concept same_as = (std::same_as<T, Types> && ...);

template<class T, class... Types>
concept is_any_of = (std::same_as<T, Types> || ...);

template<class T, class... Types>
concept different_from = (!std::same_as<T, Types> && ...);

template<class... T>
concept none = false;

template<class... T>
concept any = true;

template<class T>
concept fundamental = ::std::is_fundamental_v<T>;

template<class T>
concept real_number = ::std::is_arithmetic_v<T>;

template<class T>
concept function = ::std::is_function_v<T>;

template<class T>
concept enumeration = ::std::is_enum_v<T>;

NGS_CPT_END