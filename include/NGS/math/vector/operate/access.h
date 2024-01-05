#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_BEGIN
namespace NGS_MATH_VECTOR_CPT_NS
{
	namespace _detail_access
	{
		template<class _T>
		concept has_member = requires(_T t, index_t index) { { t.access(index) }; };
		template<class _T>
		concept has_adl = requires(_T t, index_t index) { { access(NGS_PP_PERFECT_FORWARD(t), index) }; };
	}
	template<class _V>
	concept accessable_vector = _detail_access::has_member<_V> || _detail_access::has_adl<_V> || random_access_vector<_V>;
}
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct access_t
	{
		constexpr decltype(auto) operator()(accessable_vector auto&& vector, index_t index)const
		{
			if constexpr (NGS_MATH_VECTOR_CPT_NS::_detail_access::has_member<decltype(vector)>)
			{
				return vector.access(index);
			}
			else if constexpr (NGS_MATH_VECTOR_CPT_NS::_detail_access::has_adl<decltype(vector)>)
			{
				return access(NGS_PP_PERFECT_FORWARD(vector), index);
			}
			else
			{
				return ::std::ranges::begin(vector)[index];
			}
		}
	};
}

inline constexpr _detail::access_t access{};

NGS_LIB_MODULE_END
