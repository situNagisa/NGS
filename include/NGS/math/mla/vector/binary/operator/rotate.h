#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/traits.h"
#include "NGS/math/mla/vector/expression/container.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, CVectorExpression _AngleExpression>
	requires (_Expression::dimension == _AngleExpression::dimension)
struct VectorRotateExpression : VectorExpression<VectorRotateExpression<_Expression, CVectorExpression>> {
private:
	using base_type = VectorRotateExpression::self_type;
protected:
	using self_type = VectorRotateExpression;
	using closure_type = typename vector_traits<_Expression>::closure_type;
	using angle_closure_type = typename vector_traits<_AngleExpression>::closure_type;
public:
	constexpr static size_t dimension = vector_traits<_Expression>::dimension;
	using element_type = mpl::promote_t<typename vector_traits<_Expression>::element_type, typename vector_traits<_AngleExpression>::element_type>;
public:

	constexpr VectorRotateExpression(closure_type expression, angle_closure_type radian)
		: _expression(expression)
		, _radian(radian)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		return _expression()(index) * std::cos(_radians()(index));
	}
private:
	closure_type _expression;
	angle_closure_type _radian;
};

template<CVectorExpression _Expression, CVectorExpression _AngleExpression> requires (_Expression::dimension == _AngleExpression::dimension)
constexpr auto rotate(const _Expression& expression, const _AngleExpression& radian) { return VectorRotateExpression<_Expression, _AngleExpression>(expression, radian); }
template<CVectorContainer _Container, CVectorExpression _AngleExpression> requires (_Container::dimension == _AngleExpression::dimension)
_Container& rotate_assign(_Container& container, const _AngleExpression& radian) { return container.assign(rotate(container, radian)); }

template<CVectorContainer _Container, CScalarExpression _ScalarExpression> requires (_Container::dimension == 2)
constexpr _Container& rotate_assign(_Container& container, const _ScalarExpression& radian) {

}

NGS_MLA_END
