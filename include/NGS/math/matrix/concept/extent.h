#pragma once

#include "../extent.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _T> concept dynamic_matrix = input_or_output_matrix<_T> && vectors::dynamic_vector<_T>;
template<class _T> concept adapter_matrix = input_or_output_matrix<_T> && vectors::adapter_vector<_T>;
template<class _T> concept static_matrix = input_or_output_matrix<_T> && vectors::static_extent_vector<_T>;

namespace _detail
{
	template<class _T, class _With>
	constexpr bool is_same_type()
	{
		if constexpr (static_matrix<_T>)
		{
			if constexpr (static_matrix<_With>)
			{
				return (major_extent_v<_T> == major_extent_v<_With>) && vectors::same_extent_at<_T, _With, 1>;
			}
			else if constexpr (adapter_matrix<_With>)
			{
				return vectors::same_extent_at<_T, _With, 1>;
			}
			else
			{
				return false;
			}
		}
		else if constexpr (static_matrix<_With>)
		{
			return is_same_type<_With, _T>();
		}
		else
		{
			return false;
		}
	}
}

///\brief is same extent between two vectors in compile time
template<class _L, class _R> concept same_type = _detail::is_same_type<_L, _R>();

///\brief is maybe same extent between two vectors in compile time
///\note we don't know is same type or not in compile time when the vector with dynamic extent
template<class _L, class _R> concept maybe_same_type = same_type<_L, _R> ||
((dynamic_matrix<_L> || dynamic_matrix<_R>) && vectors::maybe_same_extent_at<_L, _R, 1>);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

using vectors::static_extent;
using vectors::static_extent_v;
using vectors::static_extent_at;
using vectors::static_extent_at_v;

NGS_LIB_END