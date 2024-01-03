#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail {
	template<class _T1, class _T2>
	struct meta_cat {};

	template<template<class...>class _T1, class... _Params1, template<class...>class _T2, class... _Params2>
	struct meta_cat<_T1<_Params1...>, _T2<_Params2...>>
	{
		using type = _T1<_Params1..., _Params2...>;
	};


}

template<tuple_like _T1, tuple_like _T2>
struct meta_cat
{
	using left_modify = type_traits::add_cvref_like_t<_T1, int>;
	using right_modify = type_traits::add_cvref_like_t<_T2, int>;
	using common_type = ::std::common_reference_t<left_modify, right_modify>;
	using cat_type = typename _detail::meta_cat<type_traits::naked_t<_T1>, type_traits::naked_t<_T2>>::type;
	using type = type_traits::add_cvref_like_t<common_type, cat_type>;
};

template<tuple_like _T1, tuple_like _T2>
using meta_cat_t = typename meta_cat<_T1, _T2>::type;

NGS_LIB_MODULE_END
