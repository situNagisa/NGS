#pragma once

#include "./placeholder.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
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
using placeholder_traits = _detail::placeholder_traits_impl<type_traits::object_t<_T>>;

NGS_LIB_MODULE_END