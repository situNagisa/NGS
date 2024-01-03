#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

using depth_t = size_t;

namespace detail
{
	template<class _T>
	constexpr depth_t recurse_depth()
	{
		if constexpr (::std::ranges::range<_T>)
		{
			return recurse_depth<::std::ranges::range_value_t<_T>>() + 1;
		}
		else
		{
			return 0;
		}
	}
}

///\brief get the recurse depth of a vector 
///\note witch is the number of vector in the vector 
///\code
///depth_v<vector<vector<int>>> == 2
///\endcode
template<class _V>
inline constexpr depth_t depth_v = detail::recurse_depth<_V>();

NGS_LIB_END