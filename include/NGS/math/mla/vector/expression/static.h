#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/scalar/expression/concept.h"

NGS_MLA_BEGIN

template<CScalarExpression _ElementType, _ElementType... _Element>
struct StaticVector : VectorExpression<StaticVector<_ElementType, _Element...>> {
private:
	using base_type = StaticVector::self_type;
protected:
	using self_type = StaticVector;
public:
	using element_type = _ElementType;

	constexpr static size_t dimension = sizeof...(_Element);
	constexpr static std::array<element_type, dimension> data{_Element...};

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return data[index]; }
};

template<CScalarExpression _ElementType, _ElementType... _Element>
using static_vector_t = StaticVector<_ElementType, _Element...>;
template<CScalarExpression _ElementType, _ElementType... _Element>
inline constexpr auto static_vector_v = StaticVector<_ElementType, _Element...>();

NGS_CCPT_VERIFY(CVectorExpression, static_vector_t<int, 12, 123, 423>);

NGS_MLA_END
