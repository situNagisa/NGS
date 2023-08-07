#pragma once

#include "NGS/mla/matrix/expression/container.h"
#include "NGS/mla/scalar/expression/concept.h"

NGS_MLA_BEGIN

template<class _Expression>
concept CHomogeneousMatrix = requires() {
	typename _Expression::homogen_category;
	{ _Expression::dimension } -> std::convertible_to<size_t>;
		requires CMatrixExpression<_Expression>;
};

template<size_t _Dimension, CScalarExpression _ElementType, CMatrixLayout _Layout = tag::row, CMatrixLayout _HomoLayout = _Layout, class = std::make_index_sequence<_Dimension* (_Dimension - 1)>>
struct HomogeneousMatrix;

template<size_t _Dimension, CScalarExpression _ElementType, CMatrixLayout _Layout, CMatrixLayout _HomoLayout, size_t... _Index>
	requires (_Dimension > 1)
struct HomogeneousMatrix<
	_Dimension,
	_ElementType, _Layout, _HomoLayout,
	std::index_sequence<_Index...>> :
	MatrixContainer<
	HomogeneousMatrix<
	_Dimension, _ElementType, _Layout, _HomoLayout>,
	std::integral_constant<size_t, _Dimension>, std::integral_constant<size_t, _Dimension>,
	_ElementType, _Layout> {
private:
	using base_type = HomogeneousMatrix::self_type;
protected:
	using self_type = HomogeneousMatrix;
public:
	NGS_minherit_t(expression_type, base_type);
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(layout_category, base_type);

	NGS_minherit(row_count, base_type);
	NGS_minherit(col_count, base_type);
	NGS_minherit(element_count, base_type);

	constexpr static size_t dimension = _Dimension;

	using homogen_category = _HomoLayout;

	constexpr HomogeneousMatrix() = default;
	constexpr HomogeneousMatrix(typename base_type::template _element_i_t<_Index>... value) {
		((assign(_Index, value)), ...);
	}
	template<CMatrixExpression _Expression>
		requires is_similar<expression_type, _Expression> || (is_row_major<homogen_category> && _Expression::col_count == dimension && _Expression::row_count == dimension - 1)
	|| (is_col_major<homogen_category> && _Expression::row_count == dimension && _Expression::col_count == dimension - 1)
		constexpr HomogeneousMatrix(const _Expression & expression) {
		if constexpr (is_row_major<homogen_category>) {
			for (size_t row_index = 0; row_index < row_count - 1; row_index++)
			{
				for (size_t col_index = 0; col_index < col_count; col_index++)
				{
					assign(row_index, col_index, expression()(row_index, col_index));
				}
			}
		}
		else if constexpr (is_col_major<homogen_category>) {
			for (size_t row_index = 0; row_index < row_count; row_index++)
			{
				for (size_t col_index = 0; col_index < col_count - 1; col_index++)
				{
					assign(row_index, col_index, expression()(row_index, col_index));
				}
			}
		}
	}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		return _data[index];
	}
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if constexpr (is_row_major<homogen_category>) {
			if (row_index != row_count - 1)
				return _data[layout_category::transform(row_index, col_index, dimension - 1, dimension)];
			return col_index == col_count - 1;
		}
		else if constexpr (is_col_major<homogen_category>) {
			if (col_index != col_count - 1)
				return _data[layout_category::transform(col_index, row_index, dimension, dimension - 1)];
			return row_index == row_count - 1;
		}
	}
	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (index < dimension * (dimension - 1))
			_data[index] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) {
		if constexpr (is_row_major<homogen_category>) {
			if (row_index != row_count - 1)
				_data[layout_category::transform(row_index, col_index, dimension - 1, dimension)] = element;
		}
		else if constexpr (is_col_major<homogen_category>) {
			if (col_index != col_count - 1)
				_data[layout_category::transform(col_index, row_index, dimension, dimension - 1)] = element;
		}
		return (*this)();
	}

private:
	element_type _data[dimension * (dimension - 1)]{};
};
NGS_CCPT_VERIFY(CMatrixContainer, HomogeneousMatrix<3, int>);

NGS_MLA_END
