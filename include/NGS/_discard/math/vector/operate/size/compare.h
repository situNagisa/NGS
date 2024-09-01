#pragma once

#include "./with.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

template<input_or_output_vector _L, input_or_output_vector _R> requires maybe_same_extent<_L, _R>
constexpr bool is_same_size(_L&& left, _R&& right)
{
	if constexpr (adapter_vector<_L> || adapter_vector<_R>)
	{
		return true;
	}
	else
	{
		return NGS_LIB_MODULE_NAME::size(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right))
			== NGS_LIB_MODULE_NAME::size(NGS_PP_PERFECT_FORWARD(right), NGS_PP_PERFECT_FORWARD(left));
	}
}

#define NGS_MATH_VECTOR_CHECK_SIZE(left,right)							\
do																		\
{																		\
	if (!::std::is_constant_evaluated()){								\
		NGS_ASSERT(NGS_NS::math::vectors::ops::is_same_size(left, right));\
	}																	\
}while(false)															\
//

NGS_LIB_MODULE_END