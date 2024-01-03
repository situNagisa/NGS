#pragma once

#include "./extent.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_BEGIN

inline constexpr struct {
	constexpr extent_t operator()(static_matrix auto&& matrix)const
	{
		return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(matrix));
	}
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix, input_or_output_matrix auto&& with)const
		requires !adapter_matrix<decltype(matrix)> || !adapter_matrix<decltype(with)>
	{
		return vectors::size(NGS_PP_PERFECT_FORWARD(matrix), NGS_PP_PERFECT_FORWARD(with));
	}
}major_size{};


inline constexpr struct {
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix)const requires vectors::static_extent_vector<::std::ranges::range_value_t<decltype(matrix)>>
	{
		using minor_type = ::std::ranges::range_value_t<decltype(matrix)>;
		if constexpr (vectors::static_extent_vector<minor_type>)
		{
			return vectors::extent_v<minor_type>;
		}
		else
		{
			return ::std::ranges::size(*::std::ranges::begin(matrix));
		}
	}
	constexpr extent_t operator()(input_or_output_matrix auto&& matrix, input_or_output_matrix auto&& with)const
		requires !vectors::adapter_vector<::std::ranges::range_value_t<decltype(matrix)>> ||
	!vectors::adapter_vector<::std::ranges::range_value_t<decltype(with)>>
	{
		using matrix_minor_type = ::std::ranges::range_value_t<decltype(matrix)>;
		using with_minor_type = ::std::ranges::range_value_t<decltype(with)>;
		if constexpr (!vectors::dynamic_vector<matrix_minor_type> && !vectors::dynamic_vector<with_minor_type>)
		{
			return static_extent<matrix_minor_type, with_minor_type>;
		}
		else
		{
			return vectors::size(*::std::ranges::begin(matrix), *::std::ranges::begin(with));
		}
	}
}minor_size{};

template<extent_t _Extent, auto _DynamicSizer = major_size>
constexpr decltype(auto) default_major_sizer() { return vectors::ops::default_sizer<_Extent, _DynamicSizer>(); }

template<extent_t _Extent, auto _DynamicSizer = minor_size>
constexpr decltype(auto) default_minor_sizer() { return vectors::ops::default_sizer<_Extent, _DynamicSizer>(); }

NGS_LIB_END