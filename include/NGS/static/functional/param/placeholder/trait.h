#pragma once

#include "./placeholder.h"

NGS_STATIC_FUNCTIONAL_BEGIN

namespace detail
{

template<class _T>
struct placeholder_traits_impl;

template<template<auto>class _Template, auto _Index>
	requires std::integral<decltype(_Index)>&& requires{ typename _Template<_Index>; }
struct placeholder_traits_impl<_Template<_Index>>
{
	constexpr static auto index = _Index;
};

template<ccpt::constant _T> requires std::integral<typename _T::value_type>
struct placeholder_traits_impl<_T>
{
	constexpr static auto index = _T::value;
};

}


template<class _T>
using placeholder_traits = detail::placeholder_traits_impl<type_traits::object_t<_T>>;

NGS_STATIC_FUNCTIONAL_END