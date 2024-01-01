#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
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
using param_at = boost::fusion::result_of::value_at_c<_detail::unpack_sequence_t<typename _Pack::sequence_type>, _Index>;

template<is_packer _Pack, size_t _Index>
using param_at_t = typename param_at<_Pack, _Index>::type;

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(param_at);
NGS_LIB_MODULE_EXPORT(param_at_t);