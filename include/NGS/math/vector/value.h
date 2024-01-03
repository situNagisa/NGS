#pragma once

#include "./index.h"
#include "./defined.h"

NGS_LIB_BEGIN
namespace detail
{
	template<index_t _Index, class _V>
	struct value_at
	{
		static_assert(_Index == 0, "depth is too deep");
		using type = _V;
	};
	template<class _V>
	struct value_at<0, _V>
	{
		using type = _V;
	};

	template<index_t _Index, class _V> requires (_Index > 0)
		struct value_at<_Index, _V>
	{
		using type = typename value_at<_Index - 1, ::std::ranges::range_value_t<_V>>::type;
	};
}

///\brief get the value type of a vector
///\tparam _V
///\tparam _Index the depth of the value type
///\code
///value_t<vector3i, 0> == vector3i
///value_t<vector3i, 1> == int
///\endcode
template<class _V, index_t _Index = 0>
using value_t = typename detail::value_at<_Index, _V>::type;

NGS_LIB_END