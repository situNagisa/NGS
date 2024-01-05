#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_TRAIT_BEGIN
using dimension_t = size_t;
NGS_MATH_LA_VECTOR_TRAIT_END

NGS_MATH_LA_VECTOR_ADAPTER_BEGIN
inline constexpr traits::vectors::dimension_t dimension_dynamic = static_cast<traits::vectors::dimension_t>(-1);
inline constexpr traits::vectors::dimension_t dimension_adapter = static_cast<traits::vectors::dimension_t>(-2);
inline constexpr traits::vectors::dimension_t dimension_invalid = static_cast<traits::vectors::dimension_t>(-3);
NGS_MATH_LA_VECTOR_ADAPTER_END

NGS_MATH_LA_VECTOR_INTERFACE_BEGIN
constexpr void dimension() { }
NGS_MATH_LA_VECTOR_INTERFACE_END
NGS_MATH_LA_VECTOR_ADAPTER_BEGIN
namespace detail
{
	template<class _T, class _O = type_traits::object_t<_T>>
	constexpr functor_choice dimension_choice()
	{
		if constexpr (!requires { {_O::dimension} -> std::convertible_to<traits::vectors::dimension_t>; })
		{
			return functor_choice::none;
		}
		else if constexpr (_O::dimension == dimension_invalid)
		{
			return functor_choice::none;
		}
		else if constexpr (_O::dimension == dimension_dynamic)
		{
			if constexpr (requires(_T target) { { interfaces::vectors::dimension(NGS_PP_PERFECT_FORWARD(target))} -> std::convertible_to<traits::vectors::dimension_t>; })
			{
				return functor_choice::interface;
			}
			else if constexpr (requires(_T target) { { target.dimension() } -> std::convertible_to<traits::vectors::dimension_t>; })
			{
				return functor_choice::member;
			}
			return functor_choice::none;
		}
		return functor_choice::other;
	}
}

template<class _T> concept valid_dimension = detail::dimension_choice<_T>() != functor_choice::none;
template<class _T> concept invalid_dimension = !valid_dimension<_T>;
template<class _T>
concept adapter_dimension = valid_dimension<_T> && type_traits::object_t<_T>::dimension == dimension_adapter;

namespace detail
{
	template<class _Left, class _Right>
	constexpr traits::vectors::dimension_t static_dimension_impl()
	{
		using left_type = type_traits::object_t<_Left>;
		using right_type = type_traits::object_t<_Right>;

		if constexpr (invalid_dimension<_Left>)
		{
			return dimension_invalid;
		}
		else
		{
			constexpr traits::vectors::dimension_t left_dimension = left_type::dimension;
			if constexpr (!adapter_dimension<_Left>)
			{
				return left_dimension;
			}
			else
			{
				if constexpr (invalid_dimension<_Right>)
				{
					return dimension_invalid;
				}
				else
				{
					constexpr traits::vectors::dimension_t right_dimension = right_type::dimension;
					if constexpr (!adapter_dimension<_Right>)
					{
						return right_dimension;
					}
					else
					{
						return dimension_invalid;
					}
				}
			}
		}
	}
}

template<class _T, class _Other = void>
constexpr traits::vectors::dimension_t static_dimension = detail::static_dimension_impl<_T, _Other>();

template<class _T, class _Other = void>
concept dynamic_dimension = static_dimension<_T, _Other> == dimension_dynamic;

template<class _T, size_t _Dimension, class _Other = void>
concept dimension_equality = static_dimension<_T, _Other> == _Dimension;

namespace detail
{
	template<class _L, class _R>
	constexpr bool same_type_impl()
	{
		using left_type = type_traits::object_t<_L>;
		using right_type = type_traits::object_t<_R>;

		if constexpr (invalid_dimension<_L> || invalid_dimension<_R>)
		{
			return false;
		}
		else
		{
			constexpr traits::vectors::dimension_t left_dimension = left_type::dimension;
			constexpr traits::vectors::dimension_t right_dimension = right_type::dimension;
			if constexpr (adapter_dimension<_L> && adapter_dimension<_R>)
			{
				return false;
			}
			else if constexpr (dynamic_dimension<_L> || dynamic_dimension<_R>)
			{
				return true;
			}
			else if constexpr (adapter_dimension<_L> || adapter_dimension<_R>)
			{
				return true;
			}
			else
			{
				return left_dimension == right_dimension;
			}
		}
	}
}

template<class _L, class _R>
concept same_type = detail::same_type_impl<_L, _R>();

inline constexpr struct
{
	template<functor_choice _Choice>
	constexpr static traits::vectors::dimension_t _get_dimension_impl(valid_dimension auto&& target)
	{
		if constexpr (_Choice == functor_choice::interface)
		{
			return interfaces::vectors::dimension(NGS_PP_PERFECT_FORWARD(target));
		}
		else if constexpr (_Choice == functor_choice::member)
		{
			return target.dimension();
		}
		else if constexpr (_Choice == functor_choice::other)
		{
			return type_traits::object_t<decltype(target)>::dimension;
		}
		else
		{
			static_assert(cpt::none<decltype(target)>, "invalid dimension");
			return dimension_invalid;
		}
	}
	constexpr decltype(auto) operator()(valid_dimension auto&& target) const
	{
		constexpr auto choice = detail::dimension_choice<decltype(target)>();
		return _get_dimension_impl<choice>(NGS_PP_PERFECT_FORWARD(target));
	}
	constexpr decltype(auto) operator()(valid_dimension auto&& target, valid_dimension auto&& other)const
		requires !adapter_dimension<decltype(target)> || !adapter_dimension<decltype(other)>
	{
		if constexpr (!adapter_dimension<decltype(target)>)
		{

		}
	}
} dimension;

constexpr void assert_same_type(valid_dimension auto&& left, valid_dimension auto&& right)
{
	if constexpr (dynamic_dimension<decltype(left)> || dynamic_dimension<decltype(right)>)
	{
		NGS_ASSERT_IF_CONSTEVAL(
			vectors::dimension(NGS_PP_PERFECT_FORWARD(left)) == vectors::dimension(NGS_PP_PERFECT_FORWARD(right)),
			"dimension mismatch");
	}
	else
	{
		static_assert(same_type<decltype(left), decltype(right)>, "dimension mismatch");
	}
}

NGS_MATH_LA_VECTOR_ADAPTER_END
