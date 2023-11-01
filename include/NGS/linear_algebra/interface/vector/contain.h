#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_INTERFACE_BEGIN
constexpr void contains() {};
NGS_MATH_LA_VECTOR_INTERFACE_END
NGS_MATH_LA_VECTOR_ADAPTER_BEGIN
namespace detail
{
template<class _T>
constexpr functor_choice contains_choice()
{
	if constexpr (requires(_T target, index_t index) { {interfaces::vectors::contains(NGS_PP_PERFECT_FORWARD(target), index)} -> std::convertible_to<bool>; })
	{
		return functor_choice::interface;
	}
	else if constexpr (requires(_T target, index_t index) { {target.contains(index)} -> std::convertible_to<bool>; })
	{
		return functor_choice::member;
	}
	else
	{
		return functor_choice::none;
	}
}

}

template<class _T>
concept callable_contain = detail::contains_choice<_T>() != functor_choice::none;

inline constexpr struct
{
	constexpr decltype(auto) operator()(callable_contain auto&& target, index_t index) const
	{
		constexpr auto choice = detail::contains_choice<decltype(target)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::vectors::contains(NGS_PP_FORWARD(target), index);
		}
		else if constexpr (choice == functor_choice::member)
		{
			return NGS_PP_FORWARD(target).contains(index);
		}
	}
} contains;

NGS_MATH_LA_VECTOR_ADAPTER_END