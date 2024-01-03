#pragma once

#include "../extent.h"
#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct {
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix)const
	{
		return vectors::ops::size_at<0>(NGS_PP_PERFECT_FORWARD(matrix));
	}
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix, input_or_output_matrix auto&& with)const
		requires !adapter_matrix<decltype(matrix)> || !adapter_matrix<decltype(with)>
	{
		return vectors::ops::size(NGS_PP_PERFECT_FORWARD(matrix), NGS_PP_PERFECT_FORWARD(with));
	}
}major_size{};


inline constexpr struct {
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix)const requires vectors::static_extent_vector<::std::ranges::range_value_t<decltype(matrix)>>
	{
		return vectors::ops::size_at<1>(NGS_PP_PERFECT_FORWARD(matrix));
	}
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix, input_or_output_matrix auto&& with)const
		requires (!vectors::adapter_vector_at<decltype(matrix), 1>) || (!vectors::adapter_vector_at<decltype(with), 1>)
	{
		if constexpr (!vectors::dynamic_vector_at<decltype(matrix), 1> && !vectors::dynamic_vector_at<decltype(with), 1>)
		{
			return vectors::static_extent_at_v<decltype(matrix), decltype(with), 1>;
		}
		else
		{
			return vectors::ops::size(vectors::ops::access(NGS_PP_PERFECT_FORWARD(matrix), 0), vectors::ops::access(NGS_PP_PERFECT_FORWARD(with), 0));
		}
	}
}minor_size{};

template<extent_t _Extent, auto _DynamicSentinel = major_size>
constexpr decltype(auto) default_major_sentinel() { return vectors::ops::default_sentinel<_Extent, _DynamicSentinel>(); }

template<extent_t _Extent, auto _DynamicSentinel = minor_size>
constexpr decltype(auto) default_minor_sentinel() { return vectors::ops::default_sentinel_at<1, _Extent, _DynamicSentinel>(); }

NGS_LIB_MODULE_END