#pragma once

#include "NGS/math/mla/matrix/expression/container.h"

NGS_MLA_BEGIN

template<
	ccpt::UInt _Dimension,
	class  _ElementType,
	CMatrixTriangularTag _Category = tag::upper,
	CMatrixLayout _Layout = tag::row,
	class  = std::make_index_sequence<_Dimension::value* (_Dimension::value + 1) / 2>>
	struct NGS_API TriangularMatrix;

template<
	ccpt::UInt _Dimension,
	class  _ElementType,
	CMatrixTriangularTag _Category,
	CMatrixLayout _Layout,
	size_t... _Index
>struct NGS_API TriangularMatrix<
	_Dimension,
	_ElementType,
	_Category,
	_Layout,
	std::index_sequence<_Index...>
> : MatrixContainer<
	TriangularMatrix<
	_Dimension,
	_ElementType,
	_Category,
	_Layout>,
	_Dimension, _Dimension,
	_ElementType,
	_Layout
> {
private:
	using base_type = TriangularMatrix::self_type;
protected:
	using self_type = TriangularMatrix;
public:
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(layout_category, base_type);
	NGS_minherit_t(expression_type, base_type);
	NGS_minherit(row_count, base_type);
	NGS_minherit(col_count, base_type);
	NGS_minherit(element_count, base_type);

	using triangular_category = _Category;
	constexpr static size_t dimension = _Dimension::value;
	constexpr static size_t size = dimension * (dimension + 1) / 2;

	constexpr TriangularMatrix() = default;
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	constexpr TriangularMatrix(const _Expression& expression) {
		for (size_t row_index = 0; row_index < row_count; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				assign(row_index, col_index, expression);
			}
		}
	}
	constexpr TriangularMatrix(mpl::sequence_params_t<_Index, element_type>... value) {
		std::array<element_type, element_count> values{value...};
		size_t index = 0;
		for (size_t row_index = 0; row_index < row_count && index < sizeof...(value); row_index++)
		{
			for (size_t col_index = 0; col_index < col_count && index < sizeof...(value); col_index++)
			{
				(*this)().assign(row_index, col_index, values[index]);
				index++;
			}
		}
	}

	using base_type::operator();
	constexpr element_type operator()(size_t index) const {
		if (_HasElement(index)) {
			return _data[_Transform(index)];
		}
		return 0;
	}

	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if (_HasElement(row_index, col_index)) {
			return _data[_Transform(row_index, col_index)];
		}
		return 0;
	}

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (_HasElement(index))
			_data[_Transform(index)] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) {
		if (_HasElement(row_index, col_index)) {
			_data[_Transform(row_index, col_index)] = element;
		}
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, const CMatrixExpression auto& expression) {
		if (_HasElement(row_index, col_index)) {
			_data[_Transform(row_index, col_index)] = expression()(row_index, col_index);
		}
		return (*this)();
	}
protected:
	constexpr bool _HasElement(size_t index)const { return triangular_category::template has_element<layout_category>(index, row_count, col_count); }
	constexpr bool _HasElement(size_t row_index, size_t col_index)const { return triangular_category::has_element(row_index, col_index, row_count, col_count); }
	constexpr size_t _Transform(size_t index) const { return triangular_category::template transform<layout_category>(index, row_count, col_count); }
	constexpr size_t _Transform(size_t row_index, size_t col_index) const { return triangular_category::template transform<layout_category>(row_index, col_index, row_count, col_count); }

private:
	element_type _data[size]{};
};

template<size_t _Dimension, class  _ElementType, CMatrixTriangularTag _Category = tag::upper, CMatrixLayout _Layout = tag::row>
using triangular_matrix_t = TriangularMatrix<std::integral_constant<size_t, _Dimension>, _ElementType, _Category, _Layout>;

NGS_CCPT_VERIFY(CMatrixContainer, triangular_matrix_t<3, int>);

NGS_MLA_END
