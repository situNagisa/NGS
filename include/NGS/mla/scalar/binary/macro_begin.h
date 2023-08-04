#pragma once

#include "NGS/mla/scalar/binary/functor.h"

#define NGS_MLA_SCALAR_BINARY_FUNCTOR(op,functor,base)	\
template<class _ElementType1, class _ElementType2>		\
struct functor : base<_ElementType1, _ElementType2> {	\
private:												\
	using base_type = typename functor::self_type;		\
public:													\
	constexpr static typename base_type::result_type apply(typename base_type::argument_type1 x, typename base_type::argument_type2 y) {\
		return op;										\
	}													\
};														\
NGS_CCPT_VERIFY(CScalarBinaryFunctor, functor<int, float>)\
//
