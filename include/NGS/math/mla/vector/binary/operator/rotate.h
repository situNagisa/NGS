#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/expression/vector.h"
#include "NGS/math/mla/scalar/expression/concept.h"

NGS_MLA_BEGIN

template<CVectorExpression _Vector,CScalarExpression _Angle>
constexpr auto rotate(const _Vector& vector, _Angle angle) {
	using vector_type = Vector<_Vector::dimension,typename _Vector::element_type>;
	auto cos = std::cos(angle);
	auto sin = std::sin(angle);
	return vector_type(
		vector(0) * cos - vector(1) * sin,
		vector(0) * sin + vector(1) * cos
	);
}

NGS_MLA_END
