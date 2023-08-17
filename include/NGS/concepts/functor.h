#pragma once

#include "NGS/concepts/defined.h"

NGS_CCPT_BEGIN

template<class  _Functor = void>
concept Functor = requires() {
	typename _Functor::result_type;
};

template<template<class...>class _Functor, class... _Args>
concept FunctorTest = Functor<_Functor<_Args...>>;

NGS_CCPT_END
