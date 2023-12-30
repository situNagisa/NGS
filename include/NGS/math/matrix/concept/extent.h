#pragma once

#include "../extent.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _T> concept dynamic_matrix = input_or_output_matrix<_T> && vectors::dynamic_vector<_T>;
template<class _T> concept adapter_matrix = input_or_output_matrix<_T> && vectors::adapter_vector<_T>;
template<class _T> concept static_matrix = input_or_output_matrix<_T> && vectors::static_extent_vector<_T>;

template<class _T> concept dynamic_dynamic_matrix = dynamic_matrix<_T> && vectors::dynamic_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept dynamic_adapter_matrix = dynamic_matrix<_T> && vectors::adapter_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept dynamic_static_matrix = dynamic_matrix<_T> && vectors::static_extent_vector<::std::ranges::range_value_t<_T>>;

template<class _T> concept adapter_dynamic_matrix = adapter_matrix<_T> && vectors::dynamic_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept adapter_adapter_matrix = adapter_matrix<_T> && vectors::adapter_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept adapter_static_matrix = adapter_matrix<_T> && vectors::static_extent_vector<::std::ranges::range_value_t<_T>>;

template<class _T> concept static_dynamic_matrix = static_matrix<_T> && vectors::dynamic_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept static_adapter_matrix = static_matrix<_T> && vectors::adapter_vector<::std::ranges::range_value_t<_T>>;
template<class _T> concept static_static_matrix = static_matrix<_T> && vectors::static_extent_vector<::std::ranges::range_value_t<_T>>;

namespace _detail
{
	template<class _T, class _With>
	constexpr bool is_static_same_type()
	{
		if constexpr (static_matrix<_T>)
		{
			if constexpr (static_matrix<_With>)
			{
				return (major_extent_v<_T> == major_extent_v<_With>) && vectors::static_same_extent<::std::ranges::range_value_t<_T>, ::std::ranges::range_value_t<_With>>;
			}
			else if constexpr (adapter_matrix<_With>)
			{
				return vectors::static_same_extent<::std::ranges::range_value_t<_T>, ::std::ranges::range_value_t<_With>>;
			}
			else
			{
				return false;
			}
		}
		else if constexpr (static_matrix<_With>)
		{
			return is_static_same_type<_With, _T>();
		}
		else
		{
			return false;
		}
	}
}

///\brief is same extent between two vectors in compile time
template<class _L, class _R> concept static_same_type = _detail::is_static_same_type<_L, _R>();

///\brief is maybe same extent between two vectors in compile time
///\note we don't know is same type or not in compile time when the vector with dynamic extent
template<class _L, class _R> concept maybe_same_type =
static_same_type<_L, _R> ||
((dynamic_matrix<_L> || dynamic_matrix<_R>) && vectors::maybe_same_extent<::std::ranges::range_value_t<_L>, ::std::ranges::range_value_t<_R>>);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

using vectors::static_extent;

NGS_LIB_END