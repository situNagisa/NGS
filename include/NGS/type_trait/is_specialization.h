#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _T, template<class...>class _Template>
struct is_specialization : std::false_type {};

template<template<class...>class _Template, class... _Types>
struct is_specialization<_Template<_Types...>, _Template> : std::true_type {};

template<class _T, template<class...>class _Template>
constexpr bool is_specialization_v = is_specialization<_T, _Template>::value;

NGS_TYPE_TRAIT_END