#pragma once

#include "../element.h"
#include "./tuple.h"
#include "./defined.h"

NGS_LIB_BEGIN
namespace detail
{
	template<cpt::is_template _MastPack>
	struct unpack_sequence;

	template<template<class...>class _Template, class... _Args>
	struct unpack_sequence <_Template<_Args...>>
	{
		using type = boost::fusion::vector<_Args...>;
	};

	template<cpt::is_template _T>
	using unpack_sequence_t = typename unpack_sequence<_T>::type;

	template<class _T>
	concept element = cpt::is_template<typename type_traits::object_t<_T>::sequence_type>;

	template<class _Pack, size_t _Index>
	using element_at = boost::fusion::result_of::value_at_c<unpack_sequence_t<typename type_traits::object_t<_Pack>::sequence_type>, _Index>;

}

template<size_t _Index, detail::element _Tuple>
struct element<_Index, _Tuple> { using type = typename detail::element_at<_Tuple, _Index>::type; };

NGS_LIB_END
