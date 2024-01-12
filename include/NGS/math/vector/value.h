#pragma once

#include "./index.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<class, index_t>
	struct value {};

	template<::std::ranges::range _V, index_t _Index>
	struct value<_V, _Index> { using type = ::std::ranges::range_value_t<_V>; };

	template<statics::tuples::tuple_like _V, index_t _Index>
	struct value<_V, _Index>
	{
		using type = statics::tuples::element_t<_Index, _V>;
	};
}

template<class _V, index_t _Index = 0>
using value_t = typename detail::value<_V, _Index>::type;

namespace detail
{
	template<depth_t _Depth, class _V, index_t _Index>
	struct value_at
	{
		static_assert(_Depth == 0, "depth is too deep");
		using type = _V;
	};
	template<class _V, index_t _Index>
	struct value_at<0, _V, _Index>
	{
		using type = _V;
	};

	template<depth_t _Depth, class _V, index_t _Index>
		requires (_Depth > 0)
	struct value_at<_Depth, _V, _Index>
	{
		using type = typename value_at<_Depth - 1, value_t<_V, _Index>, _Index>::type;
	};
}

///\brief get the value type of a vector
///\tparam _V
///\tparam _Index the depth of the value type
///\code
///value_t<vector3i, 0> == vector3i
///value_t<vector3i, 1> == int
///\endcode
template<class _V, depth_t _Depth = 0, index_t _Index = 0>
using value_at_t = typename detail::value_at<_Depth, _V, _Index>::type;

NGS_LIB_END