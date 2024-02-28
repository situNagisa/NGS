#pragma once

#include "./concept.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<template_class T>
struct arg_count : ccpt::uint_<_detail::trait<type_traits::naked_t<T>>::arg_count> {};

template<template_class T>
inline constexpr auto arg_count_v = arg_count<T>::value;

NGS_LIB_MODULE_END