#pragma once

#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/scalar/expression/concept.h"

NGS_MLA_BEGIN

template<ccpt::uint _Dimension, CScalarExpression _ElementType,class = std::make_index_sequence<_Dimension::value>>
struct DiagonalMatrix;

template<ccpt::uint _Dimension,CScalarExpression _ElementType,size_t... _Index>
struct DiagonalMatrix<_Dimension,_ElementType,std::index_sequence<_Index...>> : MatrixContainer<DiagonalMatrix<_Dimension, _ElementType>,
	_Dimension, _Dimension,
	_ElementType, tag::row> {
	NGS_MPL_ENVIRON(DiagonalMatrix);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
	NGS_MPL_INHERIT_TYPE(element_type, base_type);
	constexpr static size_t dimension = _Dimension::value;

	using base_type::base_type;
	constexpr DiagonalMatrix(mpl::sequence_params_t<_Index, element_type>... value) {
		(assign(_Index, _Index, value), ...);
	}
	template<CMatrixExpression _Expression>
		requires is_similar<expression_type,_Expression>
	constexpr DiagonalMatrix(const _Expression& expression) {
		for (size_t i = 0; i < dimension; i++)
		{
			assign(i, i, expression);
		}
	}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		return _data[index];
	}
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		return (row_index == col_index) * _data[row_index];
	}

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (_HasElement(index))
			_data[index] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) {
		if (_HasElement(row_index, col_index))
			_data[_Transform(row_index,col_index)] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, const CMatrixExpression auto& expression) {
		if (_HasElement(row_index, col_index))
			_data[_Transform(row_index, col_index)] = expression()(row_index, col_index);
		return (*this)();
	}
private:
	constexpr bool _HasElement(size_t index)const {
		return index < dimension;
	}
	constexpr bool _HasElement(size_t row_index, size_t col_index)const {
		return row_index == col_index && _HasElement(row_index);
	}
	constexpr size_t _Transform(size_t row_index, size_t col_index)const {
		return row_index;
	}

private:
	std::array<element_type, dimension> _data{};
};

NGS_MLA_END
