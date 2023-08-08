#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/traits.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, size_t _Dimension = _Expression::dimension, size_t _Offset = 0>
	requires (_Offset + _Dimension <= _Expression::dimension)
struct VectorView : VectorExpression<VectorView<_Expression, _Dimension, _Offset>> {
private:
	using base_type = VectorView::self_type;
protected:
	using self_type = VectorView;
	using closure_type = typename vector_traits<_Expression>::closure_type;
public:
	constexpr static size_t dimension = _Dimension;
	using element_type = typename vector_traits<_Expression>::element_type;

	constexpr VectorView(closure_type expression)
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return _expression(index + _Offset); }
private:
	closure_type _expression;
};

NGS_MLA_END
