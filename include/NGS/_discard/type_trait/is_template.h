#pragma once


#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class T>
struct is_template : std::false_type {};

template<template<class...>class Template, class... Args>
struct is_template<Template<Args...>> : std::true_type {};

template<class T>
inline constexpr bool is_template_v = is_template<T>::value;

NGS_TYPE_TRAIT_END