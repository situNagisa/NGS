#pragma once

#include "./arg.h"

NGS_FUNCTIONAL_BEGIN

template<class _T>
struct _arg_traits;

template<template<auto>class _Template, auto _Index>
	requires std::integral<decltype(_Index)>&& requires{ typename _Template<_Index>; }
struct _arg_traits<_Template<_Index>>
{
	constexpr static auto index = _Index;
};

template<ccpt::constant _T> requires std::integral<typename _T::value_type>
struct _arg_traits<_T>
{
	constexpr static auto index = _T::value;
};

template<class _T>
struct arg_traits : _arg_traits<type_traits::object_t<_T>> {};

NGS_FUNCTIONAL_END