#pragma once

#include "./defined.h"

NGS_MATH_LA_MATRIX_INTERFACE_BEGIN
constexpr void access() {};
NGS_MATH_LA_MATRIX_INTERFACE_END
NGS_MATH_LA_MATRIX_TRAIT_BEGIN
using row_index_t = size_t;
using col_index_t = size_t;
NGS_MATH_LA_MATRIX_TRAIT_END
NGS_MATH_LA_MATRIX_ADAPTER_BEGIN

namespace detail
{
	template<class _T>
	constexpr functor_choice access_choice()
	{
		using namespace traits::matrixes;
		if constexpr (requires(_T target, row_index_t row, col_index_t col) { interfaces::matrixes::access(NGS_PP_PERFECT_FORWARD(target), row, col); })
		{
			return functor_choice::interface;
		}
		else if constexpr (requires(_T target, row_index_t row, col_index_t col) { target.access(row, col); })
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
concept accessible = detail::access_choice<_T>() != functor_choice::none;

inline constexpr struct
{
	constexpr decltype(auto) operator()(accessible auto&& target, traits::matrixes::row_index_t row, traits::matrixes::col_index_t col) const
	{
		constexpr auto choice = detail::access_choice<decltype(target)>();
		if constexpr (choice == functor_choice::interface)
		{
			return interfaces::matrixes::access(NGS_PP_PERFECT_FORWARD(target), row, col);
		}
		else if constexpr (choice == functor_choice::member)
		{
			return target.access(row, col);
		}
		else
		{
			static_assert(choice != functor_choice::none, "access is not supported");
		}
	}
} access;

NGS_MATH_LA_MATRIX_ADAPTER_END

NGS_MATH_LA_MATRIX_TRAIT_BEGIN
template<class _Type>
using value_t = type_traits::object_t<decltype(adapters::matrixes::access(declval<_Type>(), declval<row_index_t>(), declval<col_index_t>()))>;
NGS_MATH_LA_MATRIX_TRAIT_END