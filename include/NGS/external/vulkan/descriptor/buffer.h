#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<mpl::mstruct::CFlattenedStructure _LocationStruct, size_t... _ActiveIndices>
	requires ((_ActiveIndices < _LocationStruct::variable_count) && ...)
struct buffer_binder
{
	using location_struct = _LocationStruct;
	constexpr static size_t attribute_count = sizeof...(_ActiveIndices);
	constexpr static std::array<size_t, attribute_count> active_indices = { _ActiveIndices... };


};

template<class>
struct ohh {};

template<template<class...>class _T, mpl::mstruct::CVariable... _Args>
struct ohh<_T<_Args...>> : std::true_type {};

void aaa()
{
	using mpl::mstruct::variable;
	using m = mpl::mstruct::structure<int, float, float>;
	static_assert(mpl::mstruct::CFlattenedStructure<m>);

	using b = buffer_binder<m, 0, 2>;

}

NGS_LIB_MODULE_END