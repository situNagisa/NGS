#pragma once

#include "../../../defined.h"

NGS_MATH_MATRIX_BEGIN
//constexpr auto assign(cpt::none auto&&, size_t, cpt::none auto&) {}
NGS_MATH_MATRIX_END

NGS_MATH_MATRIX_FUNCTOR_BEGIN

namespace detail
{
inline constexpr struct
{
	enum class assign_type
	{
		none,
		global,
		member,
	};
	template<class _Left, class _Right, NGS_PP_CONSTEXPR_CLEAR_BUFFER>
	constexpr static auto CHOICE()
	{
		if constexpr (
			requires(_Left left, size_t row, size_t column, _Right right) { { assign(NGS_PP_PERFECT_FORWARD(left), row, column, NGS_PP_PERFECT_FORWARD(right)) }; }
		) {
			return assign_type::global;
		}
		else if constexpr (
			requires(_Left left, size_t row, size_t column, _Right right) { { left.assign(row, column, NGS_PP_PERFECT_FORWARD(right)) }; }
		) {
			return assign_type::member;
		}
		else
		{
			return assign_type::none;
		}
	}

	constexpr decltype(auto) operator()(auto&& to, size_t row, size_t column, auto&& from) const
		requires (CHOICE<decltype(to), decltype(from)>() == assign_type::global)
	{
		return assign(NGS_PP_PERFECT_FORWARD(to), row, column, NGS_PP_PERFECT_FORWARD(from));
	}
	constexpr decltype(auto) operator()(auto&& to, size_t row, size_t column, auto&& from) const
		requires (CHOICE<decltype(to), decltype(from)>() == assign_type::member)
	{
		return to.assign(row, column, NGS_PP_PERFECT_FORWARD(from));
	}
} assign{};

}

using detail::assign;

template<class _From, class _To, class _L = type_traits::object_t<_To>, class _R = type_traits::object_t<_From>>
concept assignable = requires(_L left, size_t row, size_t column, _R right)
{
	{ detail::assign(NGS_PP_PERFECT_FORWARD(left), row, column, NGS_PP_PERFECT_FORWARD(right)) };
};

NGS_MATH_MATRIX_FUNCTOR_END
