#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_ADAPTER_BEGIN
using dimension_t = size_t;
inline constexpr dimension_t dimension_dynamic = static_cast<dimension_t>(-1);
inline constexpr dimension_t dimension_invalid = static_cast<dimension_t>(-2);
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
	if constexpr (!requires { {_O::dimension} -> std::convertible_to<dimension_t>; })
	{
		return functor_choice::none;
	}
	else if constexpr (_O::dimension == dimension_invalid)
	{
		return functor_choice::none;
	}
	else if constexpr (_O::dimension == dimension_dynamic)
	{
		if constexpr (requires(_T target) { {dimension(NGS_PP_PERFECT_FORWARD(target))} -> std::convertible_to<dimension_t>; })
		{
			return functor_choice::interface;
		}
		else if constexpr (requires(_T target) { { target.dimension() } -> std::convertible_to<dimension_t>; })
		{
			return functor_choice::member;
		}
		else
		{
			return functor_choice::none;
		}
	}
	else
	{
		return functor_choice::other;
	}
}

}

template<class _T> concept valid_dimension = detail::dimension_choice<_T>() != functor_choice::none;
template<class _T> concept invalid_dimension = !valid_dimension<_T>;
template<class> constexpr dimension_t static_dimension = dimension_invalid;
template<valid_dimension _T>
constexpr dimension_t static_dimension<_T> = type_traits::object_t<_T>::dimension;

template<class _T> concept dynamic_dimension = static_dimension<_T> == dimension_dynamic;
template<class _T, size_t _Dimension> concept dimension_equality = static_dimension<_T> == _Dimension;
template<class _L, class _R>
concept same_type = dynamic_dimension<_L> || dynamic_dimension<_R> || (static_dimension<_L> == static_dimension<_R>);

inline constexpr struct
{
	constexpr decltype(auto) operator()(valid_dimension auto&& target) const
	{
		constexpr auto choice = detail::dimension_choice<decltype(target)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::vectors::dimension(NGS_PP_PERFECT_FORWARD(target));
		}
		else if constexpr (choice == functor_choice::member)
		{
			return target.dimension();
		}
		else if constexpr (choice == functor_choice::other)
		{
			return type_traits::object_t<decltype(target)>::dimension;
		}
	}
} dimension;

NGS_MATH_LA_VECTOR_ADAPTER_END
