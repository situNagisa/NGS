#pragma once

#include "NGS/math/mla/matrix/expression/homogen.h"
#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/binary/operator/product.h"
#include "NGS/math/mla/vector/unary/operator/normalize.h"
#include "NGS/math/mla/vector/expression/vector.h"
#include "NGS/math/mla/scalar/expression/concept.h"

NGS_MLA_BEGIN

template<class _ElementType = void, CMatrixLayout _Layout = tag::row, CVectorExpression _Position,CVectorExpression _Direction,CVectorExpression _Up>
	requires 
(_Position::dimension == 3) &&
(_Direction::dimension == 3) &&
(_Up::dimension == 3)
constexpr auto look_to(const _Position& position, const _Direction& direction, const _Up& up) {
	using element_type = std::conditional_t<std::same_as<void, _ElementType>,
		mpl::promote_t<typename _Position::element_type, typename _Direction::element_type, typename _Up::element_type>,
		_ElementType>;
	HomogeneousMatrix<4, element_type, _Layout> result{};

	Vector<3,element_type> f = normalize(direction);
	Vector<3, element_type> s = normalize(product_outer(f, up));
	Vector<3, element_type> u = normalize(product_outer(s, f));

	result.assign(0, 0, s(0));
	result.assign(1, 0, s(1));
	result.assign(2, 0, s(2));
	result.assign(0, 1, u(0));
	result.assign(1, 1, u(1));
	result.assign(2, 1, u(2));
	result.assign(0, 2, -f(0));
	result.assign(1, 2, -f(1));
	result.assign(2, 2, -f(2));
	result.assign(3, 0, -product_inner(s, position));
	result.assign(3, 1, -product_inner(u, position));
	result.assign(3, 2, product_inner(f, position));

	return result;
}

NGS_MLA_END
