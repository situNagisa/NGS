#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class _T, class... _Types>
concept same_as = (std::same_as<_T, _Types> && ...);

template<class _T, class... _Types>
concept is_any_of = (std::same_as<_T, _Types> || ...);

template<class _T, class... _Types>
concept different_from = (!std::same_as<_T, _Types> && ...);

template<class... _T>
concept none = false;

template<class... _T>
concept any = true;

template<class _T>
concept fundamental = std::is_fundamental_v<_T>;

template<class _T>
concept real_number = std::is_arithmetic_v<_T>;

template<class _T>
concept function = std::is_function_v < _T>;

NGS_CPT_END