#pragma once

#include "NGS/mla/scalar/binary/functor.h"

NGS_MLA_BEGIN

template<class _ElementType1, class _ElementType2>
struct ScalarMinusFunctor : ScalarBinaryFunctor<_ElementType1, _ElementType2> {
private:
	using base_type = typename ScalarMinusFunctor::self_type;
public:
	constexpr static typename base_type::result_type apply(typename base_type::argument_type1 x, typename base_type::argument_type2 y) {
		return x - y;
	}
};
NGS_CCPT_VERIFY(CScalarBinaryFunctor, ScalarMinusFunctor<int, float>);

NGS_MLA_END
