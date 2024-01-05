#pragma once

#include "NGS/math/mla/scalar/binary/functor.h"

#define NGS_MLA_SCALAR_BINARY_FUNCTOR(op,functor,base)			\
template<class  _ElementType1, class  _ElementType2>			\
struct NGS_DLL_API functor : base<_ElementType1, _ElementType2> {	\
	NGS_MPL_ENVIRON(functor);							\
public:													\
	constexpr static auto apply(typename base_type::argument_type1 x, typename base_type::argument_type2 y) {\
		return op;										\
	}													\
	using result_type = decltype(apply(std::declval<typename base_type::argument_type1>(), std::declval<typename base_type::argument_type2>()));\
};														\
NGS_CCPT_VERIFY(CScalarBinaryFunctor, functor<int, float>)\
//
