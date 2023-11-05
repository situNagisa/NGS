#pragma once

#include "./concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN

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

}

template<is_packer _Pack, size_t _Index>
using param_at = boost::fusion::result_of::value_at_c<detail::unpack_sequence_t<typename _Pack::sequence_type>, _Index>;

NGS_STATIC_FUNCTIONAL_END