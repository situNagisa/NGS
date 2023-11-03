#pragma once

#include "./trait.h"
#include "../placeholder.h"

NGS_FUNCTIONAL_BEGIN

template<class... _Types>
using parameter_pack = std::tuple<_Types...>;

namespace detail
{
enum class fixer
{
	nested_bind,
	identity,
	placeholder,
	none,
};

template<class _T>
constexpr fixer choice()
{
	constexpr bool is_binder_ = is_binder<_T>;
	constexpr bool is_placeholder_ = is_placeholder<_T>;

	if constexpr (is_binder_ && !is_placeholder_) // nested bind fixer
	{
		return fixer::nested_bind;
	}
	else if constexpr (!is_binder_ && !is_placeholder_) // identity fixer
	{
		return fixer::identity;
	}
	else if constexpr (!is_binder_ && is_placeholder_) // placeholder fixer
	{
		return fixer::placeholder;
	}
	return fixer::none;
}
}

constexpr decltype(auto) fix_arg(auto&& pack, stl::tuples::tuple_like auto&& tuple)
	requires(detail::choice<decltype((pack))>() != detail::fixer::none)
{
	using pack_type = decltype((pack));
	using tuple_type = decltype((tuple));

	constexpr auto choice = detail::choice<pack_type>();

	if constexpr (choice == detail::fixer::nested_bind)
	{
		return std::apply(NGS_PP_PERFECT_FORWARD(pack), NGS_PP_PERFECT_FORWARD(tuple));
	}
	else if constexpr (choice == detail::fixer::identity)
	{
		return pack;
	}
	else if constexpr (choice == detail::fixer::placeholder)
	{
		static_assert(arg_traits<pack_type>::index <= std::tuple_size_v<tuple_type>, "invalid pack type");
		return std::get<arg_traits<pack_type>::index - 1>(NGS_PP_PERFECT_FORWARD(tuple));
	}
	else
	{
		static_assert(cpt::none<pack_type>, "invalid pack type");
	}
}

NGS_FUNCTIONAL_END