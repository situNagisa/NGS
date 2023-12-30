#pragma once

#include "../extent.h"
#include "../concept.h"
#include "../iterator.h"
#include "./defined.h"


NGS_LIB_BEGIN

//for ADL, need to be in lib's namespace 

template<static_extent_vector _V>
constexpr extent_t size(_V&&) { return extent_v<_V>; }

NGS_LIB_END
NGS_LIB_MODULE_BEGIN



inline constexpr auto size = [](auto&& vector, auto&& with) requires !adapter_vector<decltype(vector)> || !adapter_vector<decltype(with)>
{
	if constexpr (adapter_vector<decltype(vector)>)
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(with));
	}
	else
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
	}
};

template<extent_t _Extent, auto _Dynamic = ::std::ranges::size, auto _Sentinel = make_adapter_sentinel>
constexpr auto default_sentinel()
{
	if constexpr (_Extent == dynamic_extent)
	{
		return _Dynamic;
	}
	else if constexpr (_Extent == adapter_extent)
	{
		return _Sentinel;
	}
	else
	{
		return [](auto&&...) {return _Extent; };
	}
}

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
NGS_LIB_BEGIN
namespace NGS_MATH_VECTOR_CPT_NS
{
	template<extent_t _Extent, class _DynamicSizer, class... _Args>
	concept default_sentinel_able = (_Extent != dynamic_extent) || ::std::invocable<_DynamicSizer, _Args...>;
}
NGS_LIB_END