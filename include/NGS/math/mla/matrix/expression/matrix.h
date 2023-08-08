#pragma once

#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<
	size_t _Row, size_t _Col,
	class _ElementType,
	class _Layout = tag::row,
	class = std::make_index_sequence<_Col* _Row>,
	class = std::make_index_sequence<_Row>,
	class = std::make_index_sequence<_Col>>
	struct Matrix;

template<
	size_t _Row, size_t _Col,
	class _ElementType,
	class _Layout,
	size_t... _Index,
	size_t... _RowIndex,
	size_t... _ColIndex>
struct Matrix<
	_Row, _Col,
	_ElementType,
	_Layout,
	std::index_sequence<_Index...>,
	std::index_sequence<_RowIndex...>,
	std::index_sequence<_ColIndex...>>
	: MatrixContainer<
	//derived
	Matrix<
	_Row, _Col,
	_ElementType,
	_Layout,
	std::index_sequence<_Index...>,
	std::index_sequence<_RowIndex...>,
	std::index_sequence<_ColIndex...>>,
	//row,column
	std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>,
	_ElementType,
	_Layout,
	//index_sequence
	std::index_sequence<_Index...>,
	std::index_sequence<_RowIndex...>,
	std::index_sequence<_ColIndex...>
	>{
public:
	using base_type = Matrix::self_type;
protected:
	using self_type = Matrix<
		_Row, _Col,
		_ElementType,
		_Layout,
		std::index_sequence<_Index...>,
		std::index_sequence<_RowIndex...>,
		std::index_sequence<_ColIndex...>>;
public:
	using expression_type = typename matrix_traits<base_type>::original_type;
	using element_type = typename matrix_traits<base_type>::element_type;
	NGS_minherit_t(layout_category, base_type);
	NGS_minherit(row_count, base_type);
	NGS_minherit(col_count, base_type);
public:
	constexpr Matrix() = default;
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	constexpr Matrix(const _Expression& expression) {
		for (size_t row_index = 0; row_index < row_count; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				(*this)()(row_index, col_index) = expression()(row_index, col_index);
			}
		}
	}
	constexpr Matrix(typename base_type::template _element_i_t<_Index>... value) {
		(((*this)()(_Index) = value), ...);
	}

	//===============
	// API
	//===============

	using base_type::operator();
	constexpr element_type& operator()(size_t index) { return _data[index]; }
	constexpr const element_type& operator()(size_t index)const { return _data[index]; }

	constexpr element_type& operator()(size_t row_index, size_t col_index) {
		return _data[layout_category::transform(row_index, col_index, row_count, col_count)];
	}
	constexpr const element_type& operator()(size_t row_index, size_t col_index)const {
		return _data[layout_category::transform(row_index, col_index, row_count, col_count)];
	}
	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		(*this)()(index) = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) {
		(*this)()(row_index, col_index) = element;
		return (*this)();
	}

private:
	element_type _data[row_count * col_count]{};
};

NGS_CCPT_VERIFY(CMatrixContainer, Matrix<3, 3, float>);

NGS_MLA_END
