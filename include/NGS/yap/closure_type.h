#pragma once

#include "./concept.h"

NGS_YAP_BEGIN

template<class _T>
struct expression_closure
{
	using type = _T;
};

template<CExpression _T>
struct expression_closure<_T>
{
	using type = type_traits::object_t<_T>;
};

template<class _T>
using expression_closure_t = typename expression_closure<_T>::type;

NGS_YAP_END
