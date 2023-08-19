#pragma once

#include "NGS/concepts/defined.h"

NGS_CCPT_BEGIN

template<class _Functor = void>
concept Functor = requires() {
	typename _Functor::result_type;
};

template<template<class...>class _Functor, class... _Args>
concept FunctorParameterTest = requires() {
	typename _Functor<_Args...>;
};

template<template<class...>class _Functor, class... _Args>
concept FunctorTest = FunctorParameterTest<_Functor, _Args...>&& Functor<_Functor<_Args...>>;

NGS_CCPT_END
