#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_INTERFACE_BEGIN
constexpr void access() {};
NGS_MATH_LA_VECTOR_INTERFACE_END
NGS_MATH_LA_VECTOR_ADAPTER_BEGIN

using index_t = size_t;

namespace detail
{
template<class _T>
constexpr functor_choice access_choice()
{
	if constexpr (requires(_T target, index_t index) { interfaces::vectors::access(NGS_PP_PERFECT_FORWARD(target), index); })
	{
		return functor_choice::interface;
	}
	else if constexpr (requires(_T target, index_t index) { target.access(index); })
	{
		return functor_choice::member;
	}
	else if constexpr (requires(_T target, index_t index) { target(index); })
	{
		return functor_choice::operators;
	}
	else
	{
		return functor_choice::none;
	}
}

}

template<class _T>
concept accessible = detail::access_choice<_T>() != functor_choice::none;

inline constexpr struct
{
	constexpr decltype(auto) operator()(accessible auto&& target, index_t index) const
	{
		constexpr auto choice = detail::access_choice<decltype(target)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::vectors::access(NGS_PP_PERFECT_FORWARD(target), index);
		}
		else if constexpr (choice == functor_choice::member)
		{
			return target.access(index);
		}
		else if constexpr (choice == functor_choice::operators)
		{
			return target(index);
		}
		else
		{
			static_assert(choice != functor_choice::none, "access is not supported");
		}
	}
} access;

NGS_MATH_LA_VECTOR_ADAPTER_END

NGS_MATH_LA_VECTOR_TRAIT_BEGIN
template<class _Type>
using value_t = type_traits::object_t<decltype(adapters::vectors::access(declval<_Type>(), declval<adapters::vectors::index_t>()))>;
NGS_MATH_LA_VECTOR_TRAIT_END