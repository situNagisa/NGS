#pragma once

#include "../defined.h"

NGS_MATH_VECTOR_BEGIN
constexpr auto assign(cpt::none auto&&, size_t, cpt::none auto&) {}
NGS_MATH_VECTOR_END

NGS_MATH_VECTOR_FUNCTOR_BEGIN

namespace detail
{
inline constexpr struct
{
	enum class assign_type
	{
		none,
		assign,
		member,
	};
	template<class _Left,class _Right,NGS_CONSTEXPR_CLEAR_BUFFER>
	constexpr static auto CHOICE()
	{
		if constexpr (
			requires(_Left left,size_t index,_Right right){ { assign(NGS_PERFECT_FORWARD(left),index, NGS_PERFECT_FORWARD(right)) }; }
		){
			return assign_type::assign;
		}
		else if constexpr (
			requires(_Left left, size_t index, _Right right) { { left.assign(index, NGS_PERFECT_FORWARD(right)) }; }
		){
			return assign_type::member;
		}
		else
		{
			return assign_type::none;
		}
	}

	constexpr decltype(auto) operator()(auto&& to, size_t index, auto&& from) const
		requires (CHOICE<decltype(to),decltype(from)>() == assign_type::assign)
	{
		return assign(NGS_PERFECT_FORWARD(to), index, NGS_PERFECT_FORWARD(from));
	}
	constexpr decltype(auto) operator()(auto&& to, size_t index, auto&& from) const
		requires (CHOICE<decltype(to),decltype(from)>() == assign_type::member)
	{
		return to.assign(index, NGS_PERFECT_FORWARD(from));
	}
} assign{};

}

using detail::assign;

template<class _From,class _To, class _L = type_traits::object_t<_To>,class _R = type_traits::object_t<_From>>
concept assignable = requires(_L left, size_t index,_R right)
{
	{ detail::assign(NGS_PERFECT_FORWARD(left), index, NGS_PERFECT_FORWARD(right)) };
};

NGS_MATH_VECTOR_FUNCTOR_END
