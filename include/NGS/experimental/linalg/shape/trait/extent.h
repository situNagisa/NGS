#pragma once

#include "./rank.h"
#include "./index.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using static_extent_t = ::std::size_t;

using ::std::dynamic_extent;
inline constexpr static_extent_t adaptor_extent = 0;

template<class T>
struct static_extent { constexpr static static_extent_t value(rank_t i) { return 0; } };
template<class T>
	requires ::std::is_object_v<T>&& requires(rank_t i){ { T::static_extent(i) } -> ::std::convertible_to<static_extent_t>; }
struct static_extent<T> { constexpr static static_extent_t value(rank_t i) { return static_cast<static_extent_t>(T::static_extent(i)); } };

inline constexpr struct
{
	enum class choose_type
	{
		none,
		member,
		adl,
	};

	template<class T>
	consteval static auto choose()
	{
		if constexpr (requires(T t, rank_t i) { { NGS_PP_PERFECT_FORWARD(t).extent(i) } -> ::std::convertible_to<index_t<type_traits::object_t<T>>>; })
			return choose_type::member;
		else if constexpr (requires(T t) { { extent(NGS_PP_PERFECT_FORWARD(t), 0) } -> ::std::convertible_to<index_t<type_traits::object_t<T>>>; })
			return choose_type::adl;
		
		return choose_type::none;
	}

	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(auto&& t, rank_t i) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		requires (choose<decltype(t)>() != choose_type::none)
	{
		using index_type = index_t<type_traits::object_t<decltype(t)>>;
		constexpr auto choose_v = choose<decltype(t)>();

		if constexpr (choose_v == choose_type::member)
		{
			return NGS_PP_PERFECT_FORWARD(t).extent(i);
		}
		else if constexpr (choose_v == choose_type::adl)
		{
			return extent(NGS_PP_PERFECT_FORWARD(t), i);
		}
		else
		{
			return static_cast<index_type>(0);
		}
	}
}extent{};

NGS_LIB_MODULE_END