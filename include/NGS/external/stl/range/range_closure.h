#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

#if defined(NGS_CPP_STANDARD_HAS_23)

template <class Fn, class... Types>
struct range_closure : ::std::ranges::range_adaptor_closure<range_closure<Fn, Types...>> {
	NGS_PP_INJECT_BEGIN(range_closure);
public:
	// We assume that Fn is the type of a customization point object. That means
	// 1. The behavior of operator() is independent of cvref qualifiers, so we can use `invocable<_Fn, ` without
	//    loss of generality, and
	// 2. Fn must be default-constructible and stateless, so we can create instances "on-the-fly" and avoid
	//    storing a copy.

	using function_type = Fn;
	using packet_type = ::std::tuple<Types...>;

	static_assert((::std::same_as<::std::decay_t<Types>, Types> && ...));
	static_assert(::std::is_empty_v<Fn> && ::std::is_default_constructible_v<Fn>);

	constexpr explicit range_closure(auto&&... args)
		noexcept(::std::conjunction_v<::std::is_nothrow_constructible<Types, decltype(args)>...>)
		requires (::std::same_as<::std::decay_t<decltype(args)>, Types> && ...)
		: _captures(NGS_PP_PERFECT_FORWARD(args)...)
	{}

	void operator()(auto&&) & = delete;
	void operator()(auto&&) const& = delete;
	void operator()(auto&&) && = delete;
	void operator()(auto&&) const&& = delete;

	using indices_type = ::std::index_sequence_for<Types...>;

	constexpr decltype(auto) operator()(auto&& arg) & 
		noexcept(noexcept(self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{})))
		requires ::std::invocable<function_type, decltype(arg), Types&...>
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{});
	}

	constexpr decltype(auto) operator()(auto&& arg) const &
		noexcept(noexcept(self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{})))
		requires ::std::invocable<function_type, decltype(arg), const Types&...>
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{});
	}

	constexpr decltype(auto) operator()(auto&& arg) &&
		noexcept(noexcept(self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{})))
		requires ::std::invocable<function_type, decltype(arg), Types...>
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{});
	}


	constexpr decltype(auto) operator()(auto&& arg) const &&
		noexcept(noexcept(self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{})))
		requires ::std::invocable<function_type, decltype(arg), const Types...>
	{
		return self_type::_call(*this, NGS_PP_PERFECT_FORWARD(arg), indices_type{});
	}

	template <size_t... Index>
	constexpr static decltype(auto) _call(auto&& self, auto&& arg, ::std::index_sequence<Index...>) noexcept(noexcept(function_type{}(NGS_PP_PERFECT_FORWARD(arg), ::std::get<Index>(NGS_PP_PERFECT_FORWARD(self)._captures)...)))
	{
		static_assert(::std::same_as<::std::index_sequence<Index...>, indices_type>);
		return function_type{}(NGS_PP_PERFECT_FORWARD(arg), ::std::get<Index>(NGS_PP_PERFECT_FORWARD(self)._captures)...);
	}

	packet_type _captures;
};

#endif

NGS_LIB_END