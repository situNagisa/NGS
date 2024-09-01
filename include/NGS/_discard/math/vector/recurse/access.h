#pragma once

#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	namespace access
	{
		template<class _T>
		concept accessable = input_or_output_vector<_T>;

		constexpr decltype(auto) call(auto&& vector, auto index, auto... rest)
		{
			if constexpr (sizeof...(rest))
			{
				return access::call(NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index), rest...);
			}
			else
			{
				return NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index);
			}
		}


		template<accessable _V, class = ::std::make_index_sequence<depth_v<_V> -1>>
		struct impl;

		template<accessable _V, size_t... _Index>
		struct impl<_V, ::std::index_sequence<_Index...>>
		{
			constexpr decltype(auto) operator()(_V&& vector, index_t index, type_traits::index_type_identity_t<_Index, index_t>... rest)const
			{
				return access::call(NGS_PP_PERFECT_FORWARD(vector), index, rest...);
			}
		};
	}
	template<input_or_output_vector _V>
	inline constexpr access::impl<_V> access_v{};

}

constexpr decltype(auto) access(input_or_output_vector auto&& vector, ::std::convertible_to<index_t> auto... index)
{
	static_assert(sizeof...(index) == depth_v<decltype(vector)>,
		"the number of index must be equal to the depth of vector");

	return _detail::access_v<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector), index...);
}

NGS_LIB_MODULE_END