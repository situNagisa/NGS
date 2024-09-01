#pragma once

#include "./transform.h"
#include "./transpose.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t, index_t minor, auto&& vector)const
		{
			return vectors::ops::access(NGS_PP_PERFECT_FORWARD(vector), minor);
		}
	}major_vector_transformer{};

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t major, index_t, auto&& vector)const
		{
			return vectors::ops::access(NGS_PP_PERFECT_FORWARD(vector), major);
		}
	}minor_vector_transformer{};
}

template<vectors::input_or_output_vector _V>
using major_vector_view = transform_default_sentinel_view<_detail::major_vector_transformer, 1, vectors::extent_v<_V>, _V>;

template<vectors::input_or_output_vector _V>
using minor_vector_view = transform_default_sentinel_view<_detail::minor_vector_transformer, vectors::extent_v<_V>, 1, _V>;

constexpr decltype(auto) major_vector(vectors::input_or_output_vector auto&& vector)
{
	return major_vector_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}

constexpr decltype(auto) minor_vector(vectors::input_or_output_vector auto&& vector)
{
	return minor_vector_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_MODULE_END