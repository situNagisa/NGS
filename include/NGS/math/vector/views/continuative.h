#pragma once

#include "./transform.h"
#include "./cat.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<auto _ContinuativeVector>
	struct continuative_transformer
	{
		constexpr decltype(auto) operator()(index_t index, auto&& vector)const
		{
			constexpr auto vector_extent = extent_v<decltype(vector)>;
			constexpr auto zero_vector = transform_default_sentinel_view < [](auto&&...) {return 0; }, vector_extent > {};
			constexpr auto base_vector = cat_view<decltype(zero_vector), decltype(_ContinuativeVector)>(zero_vector, _ContinuativeVector);

			return NGS_MATH_VECTOR_OPERATE_NS::access(base_vector, index) + ((index < vector_extent) * NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index));
		}
	};

	template<auto _ContinuativeVector>
	inline constexpr continuative_transformer<_ContinuativeVector> continuative_transformer_v;
}

template<static_extent_vector _V, static_extent_vector auto _ContinuativeVector>
using continuative_view = transform_default_sentinel_view<_detail::continuative_transformer_v<_ContinuativeVector>, extent_v<_V> +extent_v<decltype(_ContinuativeVector)>, _V>;

NGS_LIB_MODULE_END