#pragma once


#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _T>
struct is_template : std::false_type {};

template<template<class...>class _Template, class... _Args>
struct is_template<_Template<_Args...>> : std::true_type {};

template<class _T>
inline constexpr bool is_template_v = is_template<_T>::value;

NGS_TYPE_TRAIT_END