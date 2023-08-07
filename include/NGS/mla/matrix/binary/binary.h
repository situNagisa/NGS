#pragma once

#include "NGS/mla/matrix/expression/expression.h"
#include "NGS/mla/matrix/expression/container.h"
#include "NGS/mla/matrix/binary/functor.h"

NGS_MLA_BEGIN

template<
	CMatrixExpression _Expression1, CMatrixExpression _Expression2,
	CMatrixBinaryFunctor<_Expression1, _Expression2> _Functor,
	ccpt::UInt _Row, ccpt::UInt _Col
>class MatrixBinary : public MatrixExpression<MatrixBinary<_Expression1, _Expression2, _Functor, _Row, _Col>> {
private:
	using base_type = typename MatrixBinary::self_type;
protected:
	using self_type = MatrixBinary<_Expression1, _Expression2, _Functor, _Row, _Col>;
public:
	using expression_type = typename base_type::expression_type;
private:
	using functor_type = _Functor;
	using original_expression_type1 = typename matrix_traits<_Expression1>::original_type;
	using original_expression_type2 = typename matrix_traits<_Expression2>::original_type;

	using expression_closure_type1 = typename matrix_traits<_Expression1>::closure_type;
	using expression_closure_type2 = typename matrix_traits<_Expression2>::closure_type;
public:
	using element_type = mpl::promote_t<typename matrix_traits<_Expression1>::element_type, typename matrix_traits<_Expression2>::element_type>;

	constexpr static size_t complexity = matrix_traits<_Expression1>::complexity + matrix_traits<_Expression2>::complexity + 1;
	constexpr static size_t row_count = _Row::value;
	constexpr static size_t col_count = _Col::value;
	constexpr static size_t element_count = row_count * col_count;

	constexpr explicit MatrixBinary(expression_closure_type1 expression1, expression_closure_type2 expression2) noexcept
		: _expression1(expression1)
		, _expression2(expression2)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const { return functor_type::apply(_expression1, _expression2, row_index, col_index); }
private:
	expression_closure_type1 _expression1;
	expression_closure_type2 _expression2;
};

template<
	CMatrixExpression _Expression1, CMatrixExpression _Expression2,
	CMatrixBinaryFunctor<_Expression1, _Expression2> _Functor,
	size_t _Row = matrix_traits<_Expression1>::row_count,
	size_t _Col = matrix_traits<_Expression2>::col_count>
using matrix_binary_t = MatrixBinary<_Expression1, _Expression2, _Functor, std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>>;
//verify


template<
	CMatrixExpression _Expression1, CMatrixExpression _Expression2,
	template<class, class>class _Functor,
	size_t _Row = matrix_traits<_Expression1>::row_count,
	size_t _Col = matrix_traits<_Expression2>::col_count>
using matrix_binary_scalar_t = matrix_binary_t<
	_Expression1, _Expression2,
	MatrixBinaryScalarFunctor<_Expression1, _Expression2, _Functor<typename matrix_traits<_Expression1>::element_type, typename matrix_traits<_Expression2>::element_type>>,
	_Row, _Col>;

NGS_MLA_END
