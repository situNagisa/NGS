#pragma once

#include "NGS/mla/matrix/expression.h"
#include "NGS/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<class _Container = void>
concept CMatrixContainer = CMatrixExpression<_Container> && requires(_Container container, const _Container container_cst) {
	typename _Container::major_category;
	{ container.assign(container_cst) } -> std::convertible_to<_Container&>;
		requires (sizeof(_Container) == sizeof(typename matrix_traits<_Container>::element_type) * matrix_traits<_Container>::col_size * matrix_traits<_Container>::row_size);
};

template<size_t _Col, size_t _Row, class _ElementType, class = tag::row, class = std::make_index_sequence<_Col>, class = std::make_index_sequence<_Row>, class = std::make_index_sequence<_Col* _Row>>
struct Matrix;

template<size_t _Col, size_t _Row, class _ElementType, class _Major, size_t... _ColIndex, size_t... _RowIndex, size_t... _Index>
struct Matrix<_Col, _Row, _ElementType, _Major, std::index_sequence<_ColIndex...>, std::index_sequence<_RowIndex...>, std::index_sequence<_Index...>>
	: MatrixExpression<Matrix<_Col, _Row, _ElementType, _Major, std::index_sequence<_ColIndex...>, std::index_sequence<_RowIndex...>, std::index_sequence<_Index...>>>
{
private:
	using base_type = Matrix::self_type;
protected:
	using self_type = Matrix<_Col, _Row, _ElementType, _Major, std::index_sequence<_ColIndex...>, std::index_sequence<_RowIndex...>, std::index_sequence<_Index...>>;
public:
	using expression_type = typename matrix_traits<base_type>::original_type;
	using element_type = _ElementType;
	constexpr static size_t col_size = _Col;
	constexpr static size_t row_size = _Row;

	using major_category = _Major;
	static_assert(is_row_major<expression_type> || is_col_major<expression_type>);

	constexpr static size_t width = col_size;
	constexpr static size_t height = row_size;
protected:
	template<size_t _Index> using _element_i_t = element_type;
	template<size_t _RowI, size_t _ColI> using _element_r_c_t = element_type;
public:
	constexpr Matrix() = default;
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	constexpr Matrix(const _Expression& expression) {
		(((*this)()(_Index) = expression()(_Index)), ...);
	}
	constexpr Matrix(_element_i_t<_Index>... value) {
		(((*this)()(_Index) = value), ...);
	}

	//===============
	// API
	//===============

	using base_type::operator();
	constexpr element_type& operator()(size_t i) { return _data[i]; }
	constexpr const element_type& operator()(size_t i)const { return _data[i]; }

	constexpr element_type& operator()(size_t i, size_t j) {
		if constexpr (is_row_major<expression_type>) {
			return _data[i * col_size + j];
		}
		else {
			return _data[j * row_size + i];
		}
	}
	constexpr const element_type& operator()(size_t i, size_t j)const;

	//================
	// assign
	//================
	expression_type& assign(_element_i_t<_Index>... value) {
		(((*this)()(_Index) = value), ...);
		return (*this)();
	}

private:
	element_type _data[col_size * row_size]{};
};
//verify

NGS_MLA_END
