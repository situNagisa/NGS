#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept color = false;

template<class T, class Char>
concept printer = ::std::invocable<T, ::std::basic_string_view<Char>>;

template<class T, class Char, class Color>
concept colored_printer = printer<T, Char> && color<Color> && ::std::invocable<T, Color>;

NGS_LIB_MODULE_END