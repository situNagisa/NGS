#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/iterator_interface.h"
#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN


template<CMatrixExpression _Expressioin>
struct MatrixRowVector : VectorExpression<MatrixRowVector<_Expressioin>> {
private:
	using base_type = MatrixRowVector::self_type;
protected:
	using self_type = MatrixRowVector<_Expressioin>;
public:
	using element_type = typename matrix_traits<_Expressioin>::element_type;
	constexpr static size_t dimension = matrix_traits<_Expressioin>::col_count;
	constexpr static size_t complexity = matrix_traits<_Expressioin>::complexity + 1;
private:
	using _expression_closure_type = typename matrix_traits<_Expressioin>::closure_type;
public:
	constexpr MatrixRowVector(_expression_closure_type expression, size_t row) : _expression(expression), _row(row) {}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return _expression()(_row, index); }

private:
	_expression_closure_type _expression;
	size_t _row = 0;
};
//verify

template<CMatrixExpression _Expressioin>
struct MatrixColVector : VectorExpression<MatrixColVector<_Expressioin>> {
private:
	using base_type = MatrixColVector::self_type;
protected:
	using self_type = MatrixColVector<_Expressioin>;
public:
	using element_type = typename matrix_traits<_Expressioin>::element_type;
	constexpr static size_t dimension = matrix_traits<_Expressioin>::row_count;
	constexpr static size_t complexity = matrix_traits<_Expressioin>::complexity + 1;
private:
	using _expression_closure_type = typename matrix_traits<_Expressioin>::closure_type;
public:
	constexpr MatrixColVector(_expression_closure_type expression, size_t col) : _expression(expression), _col(col) {}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return _expression()(index, _col); }
private:
	_expression_closure_type _expression;
	size_t _col = 0;
};
//verify

template<ccpt::CRPT<CMatrixExpression<>> _Expression>
struct MatrixExpression : Expression<_Expression> {
private:
	using base_type = MatrixExpression::self_type;
protected:
	using self_type = MatrixExpression<_Expression>;
public:
	using type_category = tag::matrix;
	constexpr static size_t row_count = 0;
	constexpr static size_t col_count = 0;
	constexpr static size_t element_count = 0;

	constexpr auto row(size_t row_index)const { return MatrixRowVector<typename base_type::expression_type>((*this)(), row_index); }
	constexpr auto column(size_t col_index)const { return MatrixColVector<typename base_type::expression_type>((*this)(), col_index); }

	constexpr auto operator[](size_t row_index)const { return row(row_index); }
	//=================
	// iterator
	//=================
	/*
protected:
	template<bool _Constant>
	struct _iterator : ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type> {
	private:
		using _base_type = ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type>;
		using _self_type = _iterator<_Constant>;

		NGS_minherit_t(_reference, _base_type);
	public:
		using _base_type::_base_type;

		_reference operator*()const { return (*_base_type::_expr)()(_base_type::_n); }
	};
public:
	using iterator = _iterator<false>;
	using const_iterator = _iterator<true>;
	using reverse_iterator = boost::stl_interfaces::reverse_iterator<iterator>;
	using const_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_iterator>;

	const_iterator begin()const { return const_iterator(&(*this)(), 0); }
	const_iterator cbegin()const { return begin(); }

	const_iterator end()const { return const_iterator(&(*this)(), base_type::expression_type::element_count); }
	const_iterator cend()const { return end(); }

	const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin()const { return rbegin(); }

	const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend()const { return rend(); }

protected:
	enum class _iterator_type {
		row,
		column,
	};
	template<bool _Constant, _iterator_type _IteratorType>
	struct _element_iterator : random_access_iterator<_element_iterator<_Constant, _IteratorType>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type> {
	private:
		using _base_type = ngs::mla::random_access_iterator<_element_iterator<_Constant, _IteratorType>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type>;
		using _self_type = _element_iterator<_Constant, _IteratorType>;

		NGS_minherit_t(_reference, _base_type);
		NGS_minherit_t(_expression_ptr, _base_type);
		NGS_minherit_t(_difference_type, _base_type);
	public:
		constexpr static _iterator_type iterator_type = _IteratorType;

		using _base_type::_base_type;
		_element_iterator(_expression_ptr expr, _difference_type n, _difference_type index)
			: _base_type(expr, n)
			, _index(index)
		{}

		_reference operator*()const {
			if constexpr (iterator_type == _iterator_type::row) {
				return (*_base_type::_expr)()(_index, _base_type::_n);
			}
			else if constexpr (iterator_type == _iterator_type::column) {
				return (*_base_type::_expr)()(_base_type::_n, _index);
			}
			else {
				return (*_base_type::_expr)()(_index, _base_type::_n);
			}
		}
	private:
		_difference_type _index{};
	};
	template<bool _Constant, bool _Reverse, _iterator_type _IteratorType>
	struct _iterator_iterator :
		random_access_iterator<
		_iterator_iterator<_Constant, _Reverse, _IteratorType>,
		_Constant,
		typename base_type::expression_type,
		std::conditional_t<_Reverse, boost::stl_interfaces::reverse_iterator<_element_iterator<_Constant, _IteratorType>>, _element_iterator<_Constant, _IteratorType>>
		> {
	private:
		using _base_type = ngs::mla::random_access_iterator<
			_iterator_iterator<_Constant, _Reverse, _IteratorType>,
			_Constant,
			typename base_type::expression_type,
			std::conditional_t<_Reverse, boost::stl_interfaces::reverse_iterator<_element_iterator<_Constant, _IteratorType>>, _element_iterator<_Constant, _IteratorType>>
		>;
		using _self_type = _iterator_iterator<_Constant, _Reverse, _IteratorType>;

		NGS_minherit_t(_element_type, _base_type);
		NGS_minherit_t(_expression_type, _base_type);
	public:
		constexpr static _iterator_type iterator_type = _IteratorType;
		constexpr static bool is_reverse = _Reverse;

		_element_type operator*()const {
			using it = _element_iterator<_Constant, _IteratorType>;
			if constexpr (is_reverse) {
				if constexpr (iterator_type == _iterator_type::row) {
					return _element_type(it(_base_type::_expr, _expression_type::col_count, _base_type::_n));
				}
				else if constexpr (iterator_type == _iterator_type::column) {
					return _element_type(it(_base_type::_expr, _expression_type::row_count, _base_type::_n));
				}
			}
			else {
				return it(_base_type::_expr, 0, _base_type::_n);
			}
		}
	};
public:
	using row_iterator = _iterator_iterator<false, false, _iterator_type::column>;
	using const_row_iterator = _iterator_iterator<true, false, _iterator_type::column>;
	using row_reverse_iterator = _iterator_iterator<false, true, _iterator_type::column>;
	using const_row_reverse_iterator = _iterator_iterator<true, true, _iterator_type::column>;

	using reverse_row_iterator = boost::stl_interfaces::reverse_iterator<row_iterator>;
	using const_reverse_row_iterator = boost::stl_interfaces::reverse_iterator<const_row_iterator>;
	using reverse_row_reverse_iterator = boost::stl_interfaces::reverse_iterator<row_reverse_iterator>;
	using const_reverse_row_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_row_reverse_iterator>;

	using col_iterator = _iterator_iterator<false, false, _iterator_type::row>;
	using const_col_iterator = _iterator_iterator<true, false, _iterator_type::row>;
	using col_reverse_iterator = _iterator_iterator<false, true, _iterator_type::row>;
	using const_col_reverse_iterator = _iterator_iterator<true, true, _iterator_type::row>;

	using reverse_col_iterator = boost::stl_interfaces::reverse_iterator<col_iterator>;
	using const_reverse_col_iterator = boost::stl_interfaces::reverse_iterator<const_col_iterator>;
	using reverse_col_reverse_iterator = boost::stl_interfaces::reverse_iterator<col_reverse_iterator>;
	using const_reverse_col_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_col_reverse_iterator>;

	//========================
	// r(1)xxx_r(2)xxx
	// r1 - 内层是否反转
	// r2 - 外层是否反转
	//========================

	const_row_iterator row_begin()const { return const_row_iterator(&(*this)(), 0); }
	const_row_iterator row_cbegin()const { return row_begin(); }
	const_row_iterator row_end()const { return const_row_iterator(&(*this)(), base_type::expression_type::col_count); }
	const_row_iterator row_cend()const { return row_end(); }

	const_reverse_row_iterator row_rbegin()const { return const_reverse_row_iterator(row_end()); }
	const_reverse_row_iterator row_crbegin()const { return row_rbegin(); }
	const_reverse_row_iterator row_rend()const { return const_reverse_row_iterator(row_begin()); }
	const_reverse_row_iterator row_crend()const { return row_rend(); }

	const_row_reverse_iterator rrow_begin()const { return const_row_reverse_iterator(row_end()); }
	const_row_reverse_iterator rrow_cbegin()const { return rrow_begin(); }
	const_row_reverse_iterator rrow_end()const { return const_row_reverse_iterator(row_begin()); }
	const_row_reverse_iterator rrow_cend()const { return rrow_end(); }

	const_reverse_row_reverse_iterator rrow_rbegin()const { return const_reverse_row_reverse_iterator(row_begin()); }
	const_reverse_row_reverse_iterator rrow_crbegin()const { return rrow_rbegin(); }
	const_reverse_row_reverse_iterator rrow_rend()const { return const_reverse_row_reverse_iterator(row_end()); }
	const_reverse_row_reverse_iterator rrow_crend()const { return rrow_rend(); }

	const_col_iterator col_begin()const { return const_col_iterator(&(*this)(), 0); }
	const_col_iterator col_cbegin()const { return col_begin(); }
	const_col_iterator col_end()const { return const_col_iterator(&(*this)(), base_type::expression_type::row_count); }
	const_col_iterator col_cend()const { return col_end(); }

	const_reverse_col_iterator col_rbegin()const { return const_reverse_col_iterator(col_end()); }
	const_reverse_col_iterator col_crbegin()const { return col_rbegin(); }
	const_reverse_col_iterator col_rend()const { return const_reverse_col_iterator(col_begin()); }
	const_reverse_col_iterator col_crend()const { return col_rend(); }

	const_col_reverse_iterator rcol_begin()const { return const_col_reverse_iterator(col_end()); }
	const_col_reverse_iterator rcol_cbegin()const { return rcol_begin(); }
	const_col_reverse_iterator rcol_end()const { return const_col_reverse_iterator(col_begin()); }
	const_col_reverse_iterator rcol_cend()const { return rcol_end(); }

	const_reverse_col_reverse_iterator rcol_rbegin()const { return const_reverse_col_reverse_iterator(col_begin()); }
	const_reverse_col_reverse_iterator rcol_crbegin()const { return rcol_rbegin(); }
	const_reverse_col_reverse_iterator rcol_rend()const { return const_reverse_col_reverse_iterator(col_end()); }
	const_reverse_col_reverse_iterator rcol_crend()const { return rcol_rend(); }
	*/
};

NGS_MLA_END
