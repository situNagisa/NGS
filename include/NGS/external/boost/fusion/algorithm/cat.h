#pragma once

#include "../defined.h"

NGS_BOOST_FUSION_RESULT_OF_BEGIN

template <typename _Left, typename _Right>
struct cat;

template<template<class...>class _Template, class... _LeftArgs, class... _RightArgs>
struct cat<_Template<_LeftArgs...>, _Template<_RightArgs...>>
{
	using type = _Template<_LeftArgs..., _RightArgs...>;
};

template <typename _Left, typename _Right>
using cat_t = typename cat<_Left, _Right>::type;

NGS_BOOST_FUSION_RESULT_OF_END

NGS_BOOST_FUSION_BEGIN



NGS_BOOST_FUSION_END
