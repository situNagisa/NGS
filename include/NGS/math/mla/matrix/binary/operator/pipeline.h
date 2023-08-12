#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression, class _Functor>
	requires requires(_Expression expression, _Functor functor) { { functor(expression) }; }
constexpr auto operator|(const _Expression& expression, _Functor functor) -> decltype(functor(expression)) {
	return functor(expression);
}

NGS_MLA_END
