#pragma once

#include "./defined.h"
#include "./functor.h"
#include "./fundamental/bool.h"

NGS_CCPT_BEGIN

template<class  _Predicate = void>
concept Predicate = requires() {
	requires Functor<_Predicate>;
	requires Bool<typename _Predicate::result_type>;
};

template<template<class...>class _Predicate, class... _Args>
concept PredicateTest = Predicate<_Predicate<_Args...>>;

NGS_CCPT_END
