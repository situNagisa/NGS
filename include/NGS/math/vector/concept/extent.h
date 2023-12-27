#pragma once

#include "../extent.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _T> concept dynamic_vector = input_or_output_vector<_T> && extent_v<_T> == dynamic_extent;
template<class _T> concept adapter_vector = input_or_output_vector<_T> && extent_v<_T> == adapter_extent;
template<class _T> concept static_extent_vector = input_or_output_vector<_T> && !dynamic_vector<_T> && !adapter_vector<_T>;

namespace _detail
{
	template<class _L, class _R>
	constexpr bool is_static_same_extent()
	{
		if constexpr (static_extent_vector<_L> && static_extent_vector<_R>)
		{
			return extent_v<_L> == extent_v<_R>;
		}
		else if constexpr (adapter_vector<_L> && static_extent_vector<_R>)
		{
			return true;
		}
		else if constexpr (static_extent_vector<_L> && adapter_vector<_R>)
		{
			return true;
		}
		else if constexpr (adapter_vector<_L> && adapter_vector<_R>)
		{
			return false;
		}
		return false;
	}
}

///\brief is same extent between two vectors in compile time
template<class _L, class _R> concept static_same_extent = _detail::is_static_same_extent<_L, _R>();

///\brief is maybe same extent between two vectors in compile time
///\note we don't know is same type or not in compile time when the vector with dynamic extent
template<class _L, class _R> concept maybe_same_extent = static_same_extent<_L, _R> || (dynamic_vector<_L> || dynamic_vector<_R>);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

template<class _V, class _With> requires (adapter_vector<_V> && !adapter_vector<_With>) || !adapter_vector<_V>
constexpr extent_t static_extent = adapter_vector<_V> ? extent_v<_With> : extent_v<_V>;

NGS_LIB_END