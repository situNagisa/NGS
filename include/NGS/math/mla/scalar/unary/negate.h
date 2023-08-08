#pragma once

#include "NGS/math/mla/scalar/unary/functor.h"

NGS_MLA_BEGIN

template<class _ElementType>
struct ScalarNegateFunctor : ScalarUnaryFunctor<_ElementType> {
private:
	using base_type = typename ScalarNegateFunctor::self_type;
public:
	constexpr static typename base_type::result_type apply(typename base_type::argument_type x) {
		return -x;
	}
};
NGS_CCPT_VERIFY(CScalarUnaryFunctor, ScalarNegateFunctor<int>);

NGS_MLA_END
