#pragma once

#include "./concept.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<container _T>
struct closure<_T>
{
	using type = std::add_lvalue_reference_t<_T>;
};

NGS_MATH_VECTOR_FUNCTOR_END
