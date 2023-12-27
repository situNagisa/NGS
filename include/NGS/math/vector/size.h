#pragma once

#include "./extent.h"
#include "./concept.h"

NGS_LIB_BEGIN

template<static_extent_vector _V>
constexpr extent_t size(_V&&) { return extent_v<_V>; }

template<input_or_output_vector _Vector, input_or_output_vector _With>
	requires (adapter_vector<_Vector> && !adapter_vector<_With>) || !adapter_vector<_Vector>
constexpr extent_t size(_Vector && vector, _With && with)
{
	if constexpr (adapter_vector<_Vector>)
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(with));
	}
	else
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
	}
}

template<input_or_output_vector _L, input_or_output_vector _R> requires maybe_same_extent<_L, _R>
constexpr bool is_same_size(_L&& left, _R&& right)
{
	return NGS_LIB_NAME::size(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right))
		== NGS_LIB_NAME::size(NGS_PP_PERFECT_FORWARD(right), NGS_PP_PERFECT_FORWARD(left));
}

#define NGS_MATH_VECTOR_CHECK_SIZE(left,right)							\
do																		\
{																		\
	if (!::std::is_constant_evaluated()){								\
		NGS_ASSERT(NGS_NS::math::vectors::is_same_size(left, right));	\
	}																	\
}while(false)															\
//


NGS_LIB_END