#pragma once

#include "NGS/math/mla/matrix/unary/unary.h"
#include "NGS/math/mla/matrix/unary/operator/triangular.h"
#include "NGS/math/mla/matrix/expression/square.h"
#include "NGS/math/mla/matrix/expression/matrix.h"

NGS_MLA_BEGIN

template<CMatrixSquare _Expression, CMatrixLayout _Layout = tag::row>
	requires (_Expression::row_count > 1)
struct NGS_API MatrixGaussianElimination : triangular_matrix_t<_Expression::row_count, typename _Expression::element_type, tag::upper, _Layout> {
	NGS_menvironment(MatrixGaussianElimination);
public:
	NGS_minherit_t(expression_type, base_type);
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(layout_category, base_type);

	NGS_minherit(row_count, base_type);
	NGS_minherit(col_count, base_type);

	constexpr static size_t dimension = _Expression::row_count;
	constexpr static size_t complexity = matrix_traits<_Expression>::complexity + 1;
private:
	using original_expression_type = typename matrix_traits<_Expression>::original_type;
	using expression_closure_type = typename matrix_traits<_Expression>::closure_type;
	using factor_type = triangular_matrix_t<dimension - 1, element_type, tag::lower>;
public:
	constexpr explicit MatrixGaussianElimination(expression_closure_type expression) noexcept
		: base_type(expression)
	{
		factor_type factor{};
		for (size_t index = 1; index < dimension; index++)
		{
			size_t row_index = index;
			for (size_t col_index = 0; col_index < index; col_index++)
			{
				factor.assign(row_index - 1, col_index, _SolveFactor(expression, factor, row_index, col_index));
			}
			for (size_t col_index = index; col_index < dimension; col_index++)
			{
				base_type::assign(row_index, col_index, _Solve(expression, factor, row_index, col_index));
			}
		}
	}
private:
	/**
	 * @brief solve the value
	 *
	 * result = (a[row,col] - sigma[0,col - 1] -> [i](result[row,i] * a[i,col])
	 *
	 * \param row_index
	 * \param col_index
	 * \return
	 */
	constexpr element_type _Solve(expression_closure_type expression, const factor_type& factor, size_t row_index, size_t col_index)const {
		element_type sum = 0;
		size_t col = col_index > row_index ? row_index : col_index;
		for (size_t index = 0; index < col; index++)
		{
			sum += factor(row_index - 1, index) * (*this)()(index, col_index);
		}
		if (base_type::_HasElement(row_index, col_index))
			return (*this)()(row_index, col_index) - sum;
		return expression()(row_index, col_index) - sum;
	}

	/**
	 * @brief solve the factor at element(row_index,col_index)
	 *
	 * result = value[row_index,col_index] / a[row - 1,col]
	 *
	 * @param row_index
	 * @param col_index
	 * @return the factor
	 */
	constexpr element_type _SolveFactor(expression_closure_type expression, const factor_type& factor, size_t row_index, size_t col_index)const {
		return _Solve(expression, factor, row_index, col_index) / (*this)()(col_index, col_index);
	}
};

struct NGS_API _GaussianElimination {
	constexpr _GaussianElimination() = default;

	template<CMatrixSquare _Expression>
	constexpr auto operator()(const _Expression& expression)const {
		constexpr size_t dimension = _Expression::row_count;
		if constexpr (dimension == 1) {
			return expression;
		}
		else {
			return MatrixGaussianElimination<_Expression>(expression);
		}
	}
};
//inline constexpr _GaussianElimination gaussian_elimination{};

template<CMatrixSquare _Expression>
constexpr auto gaussian_elimination(const _Expression& expression) {
	constexpr size_t dimension = _Expression::row_count;
	if constexpr (dimension == 1) {
		return expression;
	}
	else {
		return MatrixGaussianElimination<_Expression>(expression);
	}
}

NGS_MLA_END
