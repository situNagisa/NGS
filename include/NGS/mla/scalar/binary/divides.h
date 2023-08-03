#pragma once

#include "NGS/mla/scalar/binary/functor.h"

NGS_MLA_BEGIN

template<class _ElementType1, class _ElementType2>
struct ScalarDividesFunctor : ScalarBinaryFunctor<_ElementType1, _ElementType2> {
private:
	using base_type = typename ScalarDividesFunctor::self_type;
public:
	constexpr static typename base_type::result_type apply(typename base_type::argument_type1 x, typename base_type::argument_type2 y) {
		return x / y;
	}
};
NGS_CCPT_VERIFY(CScalarBinaryFunctor, ScalarDividesFunctor<int, float>);

NGS_MLA_END
