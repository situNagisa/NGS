#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class L, class R>
	concept bit_or_has_member = ::std::same_as<::std::remove_cvref_t<L>, ::std::remove_cvref_t<R>> && requires(L l, R r)
	{
		NGS_PP_PERFECT_FORWARD(l).bit_or(NGS_PP_PERFECT_FORWARD(r));
	};

	template<class L,class R>
	concept bit_or_has_adl = requires(L l, R r)
	{
		bit_or(NGS_PP_PERFECT_FORWARD(l), NGS_PP_PERFECT_FORWARD(r));
	};

	template<class L, class R>
	concept bit_and_has_member = ::std::same_as<::std::remove_cvref_t<L>, ::std::remove_cvref_t<R>>&& requires(L l, R r)
	{
		NGS_PP_PERFECT_FORWARD(l).bit_and(NGS_PP_PERFECT_FORWARD(r));
	};

	template<class L, class R>
	concept bit_and_has_adl = requires(L l, R r)
	{
		bit_and(NGS_PP_PERFECT_FORWARD(l), NGS_PP_PERFECT_FORWARD(r));
	};

	template<class L, class R>
	concept bit_xor_has_member = ::std::same_as<::std::remove_cvref_t<L>, ::std::remove_cvref_t<R>>&& requires(L l, R r)
	{
		NGS_PP_PERFECT_FORWARD(l).bit_xor(NGS_PP_PERFECT_FORWARD(r));
	};

	template<class L, class R>
	concept bit_xor_has_adl = requires(L l, R r)
	{
		bit_xor(NGS_PP_PERFECT_FORWARD(l), NGS_PP_PERFECT_FORWARD(r));
	};

	template<class T>
	concept bit_not_has_member = requires(T t)
	{
		NGS_PP_PERFECT_FORWARD(t).bit_not();
	};

	template<class T>
	concept bit_not_has_adl = requires(T t)
	{
		bit_not(NGS_PP_PERFECT_FORWARD(t));
	};

	inline constexpr struct
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& left, const auto& right
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return static_cast<bool>(left) || static_cast<bool>(right);
		}
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& tuple
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return operator()(::std::get<0>(tuple), ::std::get<1>(tuple));
		}
	}bit_or{};

	inline constexpr struct
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& left, const auto& right
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return static_cast<bool>(left) && static_cast<bool>(right);
		}
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& tuple
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return operator()(::std::get<0>(tuple), ::std::get<1>(tuple));
		}
	} bit_and{};

	inline constexpr struct
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& left, const auto& right
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return static_cast<bool>(left) ^ static_cast<bool>(right);
		}
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& tuple
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return operator()(::std::get<0>(tuple), ::std::get<1>(tuple));
		}
	} bit_xor{};

	inline constexpr struct
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr bool operator()(
			const auto& b
			) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			return !static_cast<bool>(b);
		}
	} bit_not{};
}

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		const concepts::range auto& left, const concepts::range auto& right,
		::std::output_iterator<bool> auto result
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		return ::std::ranges::transform(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right), result, _detail::bit_or);
	}

	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		concepts::range auto&& left, concepts::range auto&& right
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (_detail::bit_or_has_member<decltype(left), decltype(right)>)
			return NGS_PP_PERFECT_FORWARD(left).bit_or(NGS_PP_PERFECT_FORWARD(right));
		else if constexpr (_detail::bit_or_has_adl<decltype(left), decltype(right)>)
			return bit_or(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
		else
		{
			return ::std::views::transform(::std::views::zip(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)), _detail::bit_or);
		}
	}
}bit_or{};

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		const concepts::range auto& left, const concepts::range auto& right,
		::std::output_iterator<bool> auto output
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		return ::std::ranges::transform(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right), output, _detail::bit_and);
	}
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		concepts::range auto&& left, concepts::range auto&& right
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (_detail::bit_and_has_member<decltype(left), decltype(right)>)
			return NGS_PP_PERFECT_FORWARD(left).bit_and(NGS_PP_PERFECT_FORWARD(right));
		else if constexpr (_detail::bit_and_has_adl<decltype(left), decltype(right)>)
			return bit_and(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
		else
		{
			return ::std::views::transform(::std::views::zip(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)), _detail::bit_and);
		}
	}
} bit_and{};

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		const concepts::range auto& left, const concepts::range auto& right,
		::std::output_iterator<bool> auto output
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		return ::std::ranges::transform(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right), output, _detail::bit_xor);
	}
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		concepts::range auto&& left, concepts::range auto&& right
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (_detail::bit_xor_has_member<decltype(left), decltype(right)>)
			return NGS_PP_PERFECT_FORWARD(left).bit_xor(NGS_PP_PERFECT_FORWARD(right));
		else if constexpr (_detail::bit_xor_has_adl<decltype(left), decltype(right)>)
			return bit_xor(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
		else
		{
			return ::std::views::transform(::std::views::zip(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)), _detail::bit_xor);
		}
	}
} bit_xor{};

inline constexpr struct
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		const concepts::range auto& range,
		::std::output_iterator<bool> auto output
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		return ::std::ranges::transform(NGS_PP_PERFECT_FORWARD(range), output, _detail::bit_not);
	}
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(
		concepts::range auto&& range
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (_detail::bit_not_has_member<decltype(range)>)
			return NGS_PP_PERFECT_FORWARD(range).bit_not();
		else if constexpr (_detail::bit_not_has_adl<decltype(range)>)
			return bit_not(NGS_PP_PERFECT_FORWARD(range));
		else
		{
			return ::std::views::transform(range, _detail::bit_not);
		}
	}
} bit_not{};


NGS_LIB_MODULE_END