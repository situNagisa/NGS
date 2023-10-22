#pragma once

#include "./defined.h"
#include "./functor.h"
#include "./fundamental/boolean.h"

NGS_CCPT_BEGIN

template<class  _Predicate = void>
concept predicate = requires() {
	requires Functor<_Predicate>;
	requires boolean<typename _Predicate::result_type>;
};

template<template<class...>class _Predicate, class... _Args>
concept predicate_test = predicate<_Predicate<_Args...>>;

NGS_CCPT_END
