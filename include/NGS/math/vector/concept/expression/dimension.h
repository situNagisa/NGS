#pragma once

#include "../../defined.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

inline constexpr size_t invalid_dimension = -1;

template<class>
inline constexpr size_t dimension = invalid_dimension;

template<class _Vector>
	requires requires{ { type_traits::object_t<_Vector>::dimension } -> std::convertible_to<size_t>; }
inline constexpr size_t dimension<_Vector> = type_traits::object_t<_Vector>::dimension;

template<class _T,class _O = type_traits::object_t<_T>>
concept valid_dimension = dimension<_O> != invalid_dimension;

NGS_MATH_VECTOR_FUNCTOR_END
