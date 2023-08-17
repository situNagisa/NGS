#pragma once

#include "NGS/math/mla/vector/expression/expression.h"

NGS_MLA_BEGIN

template<ccpt::UInt _Dim, class  _ElementType>
class NGS_API  VectorScalarExpression : public VectorExpression<VectorScalarExpression<_Dim, _ElementType>> {
private:
	using base_type = typename VectorScalarExpression::self_type;
protected:
	using self_type = VectorScalarExpression<_Dim, _ElementType>;
public:
	using element_type = _ElementType;
	constexpr static size_t dimension = _Dim::value;

	constexpr explicit VectorScalarExpression(element_type scalar) noexcept
		: _scalar(scalar)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t i)const { return _scalar; }

private:
	element_type _scalar;
};
NGS_CCPT_VERIFY(CVectorExpression, VectorScalarExpression<std::integral_constant<size_t, 3>, int>);

template<size_t _Dim, class  _ElementType>
using vector_scalar_expression_t = VectorScalarExpression<std::integral_constant<size_t, _Dim>, _ElementType>;

NGS_MLA_END
