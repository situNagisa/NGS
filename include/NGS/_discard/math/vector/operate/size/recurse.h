#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class, index_t _Index, class = ::std::make_index_sequence<_Index + 1>>
	struct static_extent_concept;

	template<class _V, index_t _Index, size_t... _Indexes>
	struct static_extent_concept<_V, _Index, ::std::index_sequence<_Indexes...>>
		: ::std::bool_constant<(static_extent_vector_at<_V, _Indexes> && ...)> {};

	template<index_t _Index>
	constexpr extent_t size(input_or_output_vector auto&& vector)
	{
		using vector_type = decltype(vector);

		if constexpr (_Index)
		{
			static_assert(
				!adapter_vector<vector_type>,
				"size() is not supported for adapter_vector"
				);
			return _detail::size<_Index - 1>(*::std::ranges::begin(vector));
		}
		else
		{
			return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
		}
	}

	template<index_t _Index>
	struct size_at_t {
		constexpr extent_t operator()(input_or_output_vector auto&& vector)const requires (_Index < (depth_v<decltype(vector)>))
		{
			using vector_type = decltype(vector);

			if constexpr (static_extent_concept<vector_type, _Index>::value)
			{
				return extent_at_v<vector_type, _Index>;
			}
			else
			{
				return _detail::size<_Index>(NGS_PP_PERFECT_FORWARD(vector));
			}
		}
	};
}

template<index_t _Index>
inline constexpr _detail::size_at_t<_Index> size_at{};

NGS_LIB_MODULE_END