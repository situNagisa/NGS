#pragma once

#include "./concept.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _T>
struct closure
{
	using type = yap::expression_closure_t<_T>;
};

template<expression _T>
struct closure<_T>
{
	using type = yap::expression_closure_t<_T>;
};

template<class _T>
using closure_t = typename closure<_T>::type;

NGS_MATH_VECTOR_FUNCTOR_END
