#pragma once

#include "../concept.h"
#include "./size.h"
#include "./defined.h"

NGS_LIB_BEGIN
namespace NGS_MATH_VECTOR_CPT_NS
{
	template<class _L, class _R>
	concept assignable_from = output_vector<_L, ::std::ranges::range_value_t<_R>> && ((input_vector<_R>&& maybe_same_extent<_L, _R>) || ::std::ranges::random_access_range<_R>);
}
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

namespace _detail
{
	void assign() = delete;

	struct assign_t
	{
		constexpr void operator()(auto&& output, auto&& input)const requires assignable_from<decltype(output), decltype(input)>
		{
			if constexpr (requires{ NGS_PP_PERFECT_FORWARD(output).assign(NGS_PP_PERFECT_FORWARD(input)); })
			{
				NGS_PP_PERFECT_FORWARD(output).assign(NGS_PP_PERFECT_FORWARD(input));
			}
			else if constexpr (requires{ assign(NGS_PP_PERFECT_FORWARD(output), NGS_PP_PERFECT_FORWARD(input)); })
			{
				assign(NGS_PP_PERFECT_FORWARD(output), NGS_PP_PERFECT_FORWARD(input));
			}
			else
			{
				NGS_MATH_VECTOR_CHECK_SIZE(output, input);
				::std::ranges::copy(NGS_PP_PERFECT_FORWARD(input), ::std::ranges::begin(output));
			}
		}
	};
}

inline constexpr _detail::assign_t assign{};

NGS_LIB_MODULE_END