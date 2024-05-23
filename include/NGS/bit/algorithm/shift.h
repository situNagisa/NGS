#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class T>
	concept right_shift_has_member = requires(T t, ::std::size_t shift)
	{
		NGS_PP_PERFECT_FORWARD(t).right_shift(shift);
	};

	template<class T>
	concept right_shift_has_adl = requires(T t, ::std::size_t shift)
	{
		right_shift(NGS_PP_PERFECT_FORWARD(t),shift);
	};

	template<class T>
	concept left_shift_has_member = requires(T t, ::std::size_t shift)
	{
		NGS_PP_PERFECT_FORWARD(t).left_shift(shift);
	};

	template<class T>
	concept left_shift_has_adl = requires(T t, ::std::size_t shift)
	{
		left_shift(NGS_PP_PERFECT_FORWARD(t), shift);
	};
}

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(concepts::range auto&& bitset, ::std::size_t shift, ::std::output_iterator<bool> auto result) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		for (auto&& source : NGS_PP_PERFECT_FORWARD(bitset) | ::std::views::drop(shift))
		{
			*result = source;
			++result;
		}
		for (::std::size_t i = 0; i < shift; i++)
		{
			*result = false;
			++result;
		}

		return result;
	}
	/*
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(concepts::range auto&& bitset, ::std::size_t shift) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		using type = decltype(bitset);

		if constexpr (_detail::right_shift_has_member<type>)
		{
			return NGS_PP_PERFECT_FORWARD(bitset).right_shift(shift);
		}
		else if constexpr (_detail::right_shift_has_adl<type>)
		{
			return right_shift(NGS_PP_PERFECT_FORWARD(bitset), shift);
		}
		else
		{
			return ::std::views::transform(NGS_PP_PERFECT_FORWARD(bitset) | ::std::views::enumerate, [shift, size = ::std::ranges::size(bitset)](auto&& t)
				{
					auto&& [index, source] = NGS_PP_PERFECT_FORWARD(t);
					return static_cast<bool>(index < (size - shift)) * source;
				});
		}
	}
	*/
}right_shift{};

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(concepts::range auto&& bitset, ::std::size_t shift, ::std::output_iterator<bool> auto result) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		return right_shift(NGS_PP_PERFECT_FORWARD(bitset) | ::std::views::reverse, shift, result);
	}
	/*
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(concepts::output_range auto&& bitset, ::std::size_t shift) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		using type = decltype(bitset);

		if constexpr (_detail::left_shift_has_member<type>)
		{
			NGS_PP_PERFECT_FORWARD(bitset).left_shift(shift);
		}
		else if constexpr (_detail::left_shift_has_adl<type>)
		{
			left_shift(NGS_PP_PERFECT_FORWARD(bitset), shift);
		}
		else
		{
			right_shift(bitset | ::std::views::reverse, shift);
		}
	}
	*/

}left_shift{};

NGS_LIB_MODULE_END