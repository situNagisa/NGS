#pragma once

#include "../concept.h"

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

template<class _T>
using closure_param_t = std::conditional_t<std::is_reference_v<_T>, _T, const _T&>;

NGS_MATH_VECTOR_FUNCTOR_END
