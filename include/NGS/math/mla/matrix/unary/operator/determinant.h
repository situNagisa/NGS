#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/matrix/expression/square.h"
#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/traits.h"
#include "NGS/math/mla/matrix/unary/operator/gauss_elimination.h"

NGS_MLA_BEGIN

struct _Determinant {
	constexpr _Determinant() = default;

	template<CSquareMatrix _Expression>
	constexpr auto operator()(const _Expression& expression)const {
		using element_type = typename matrix_traits<_Expression>::element_type;
		using container_type = triangular_matrix_t<_Expression::row_count, element_type>;
		element_type result{ 1 };
		container_type U = gaussian_elimination(expression);
		for (size_t i = 0; i < container_type::dimension; i++)
		{
			result *= U(i, i);
		}
		return result;
	}
};
//inline constexpr _Determinant determinant{};

template<CSquareMatrix _Expression>
constexpr auto determinant(const _Expression& expression) {
	using element_type = typename matrix_traits<_Expression>::element_type;
	using container_type = triangular_matrix_t<_Expression::row_count, element_type>;
	element_type result{ 1 };
	container_type U = gaussian_elimination(expression);
	for (size_t i = 0; i < container_type::dimension; i++)
	{
		result *= U(i, i);
	}
	return result;
}

NGS_MLA_END
