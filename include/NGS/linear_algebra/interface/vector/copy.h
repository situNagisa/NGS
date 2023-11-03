#pragma once

#include "./assign.h"
#include "./dimension.h"
#include "./contain.h"

NGS_MATH_LA_VECTOR_INTERFACE_BEGIN
constexpr void copy() {};
NGS_MATH_LA_VECTOR_INTERFACE_END
NGS_MATH_LA_VECTOR_ADAPTER_BEGIN

namespace detail
{
template<class _L, class _R>
constexpr functor_choice copy_choice()
{
	if constexpr (requires(_L left, _R right) { interfaces::vectors::copy(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); })
	{
		return functor_choice::interface;
	}
	else if constexpr (requires(_L left, _R right) { left.copy(NGS_PP_PERFECT_FORWARD(right)); })
	{
		return functor_choice::member;
	}
	else if constexpr (same_type<_L, _R> && requires
	{
		requires accessible<_R>;
		requires assignable<_L, traits::vectors::value_t<_R>>;
	})
	{
		return functor_choice::other;
	}
	else
	{
		return functor_choice::none;
	}
}

}

template<class _L, class _R = _L>
concept copyable = detail::copy_choice<_L, _R>() != functor_choice::none;

inline constexpr struct
{
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires copyable<decltype(left), decltype(right)>
	{
		constexpr auto choice = detail::copy_choice<decltype(left), decltype(right)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::vectors::copy(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
		}
		else if constexpr (choice == functor_choice::member)
		{
			return left.copy(NGS_PP_PERFECT_FORWARD(right));
		}
		else if constexpr (choice == functor_choice::other)
		{
			if constexpr (dynamic_dimension<decltype(left)> || dynamic_dimension<decltype(right)>)
			{
				NGS_ASSERT_IF_CONSTEVAL(dimension(left) == dimension(right), "dimension mismatch");
			}

			for (index_t i = 0; i < dimension(left); i++)
			{
				if constexpr (callable_contain<decltype(left)>)
				{
					if (!contains(left, i))
						continue;
				}
				assign(left, i, access(right, i));
			}
		}
		else
		{
			static_assert(choice != functor_choice::none, "copy is not supported");
		}
	}
} copy;

NGS_MATH_LA_VECTOR_ADAPTER_END