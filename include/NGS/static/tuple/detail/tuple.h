#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace static_tuple_adl
{
	template<class...>
	struct static_tuple
	{
		NGS_PP_INJECT_BEGIN(static_tuple);
	public:
	};

	template<class First, class... Rest>
	struct static_tuple<First, Rest...> : static_tuple<Rest...>
	{
		NGS_PP_INJECT(static_tuple);
	public:
		using value_type = First;

		constexpr static_tuple() noexcept = default;
		constexpr explicit(false) static_tuple(auto&& first, auto&&... rest) noexcept
			: base_type(NGS_PP_PERFECT_FORWARD(rest)...)
			, _data(NGS_PP_PERFECT_FORWARD(first))
		{}

#if defined(__cpp_explicit_this_parameter)
		constexpr auto&& _base(this auto&& self) { return static_cast<type_traits::add_cvref_like_t<base_type, decltype(self)>>(*this); }
		constexpr auto&& _value(this auto&& self) { return _data; }
		constexpr auto&& _value(this self_type&& self) { return ::std::move(_data); }
		constexpr auto&& _value(this const self_type&& self) { return static_cast<::std::add_rvalue_reference_t<::std::add_const_t<value_type>>>(_data); }
#else
		constexpr auto&& _base()& { return static_cast<base_type&>(*this); }
		constexpr auto&& _base() const& { return static_cast<const base_type&>(*this); }
		constexpr auto&& _base()&& { return static_cast<base_type&&>(*this); }
		constexpr auto&& _base() const&& { return static_cast<const base_type&&>(*this); }

		constexpr auto&& _value()& { return _data; }
		constexpr auto&& _value() const& { return _data; }
		constexpr auto&& _value()&& { return ::std::move(_data); }
		constexpr auto&& _value() const&& { return _data; }
#endif
	public:
		//this `public` is for `structured type` which can be passed to non-type template parameter
		value_type _data;
	};

	template<::std::size_t I>
	constexpr decltype(auto) get_impl(auto&& p) noexcept
		requires (I < size_v<::std::remove_cvref_t<decltype(p)>>)
	{
		using tuple_type = ::std::remove_cvref_t<decltype(p)>;
		if constexpr (I == size_v<tuple_type> -1)
		{
			return NGS_PP_PERFECT_FORWARD(p)._value();
		}
		else
		{
			return static_tuple_adl::get_impl<I>(NGS_PP_PERFECT_FORWARD(p)._base());
		}
	}

	template<size_t I, class... Args>
	constexpr decltype(auto) get(static_tuple<Args...>& t) { return static_tuple_adl::get_impl<sizeof...(Args) - 1 - I>(NGS_PP_PERFECT_FORWARD(t)); }
	template<size_t I, class... Args>
	constexpr decltype(auto) get(const static_tuple<Args...>& t) { return static_tuple_adl::get_impl<sizeof...(Args) - 1 - I>(NGS_PP_PERFECT_FORWARD(t)); }
	template<size_t I, class... Args>
	constexpr decltype(auto) get(static_tuple<Args...>&& t) { return static_tuple_adl::get_impl<sizeof...(Args) - 1 - I>(NGS_PP_PERFECT_FORWARD(t)); }
	template<size_t I, class... Args>
	constexpr decltype(auto) get(const static_tuple<Args...>&& t) { return static_tuple_adl::get_impl<sizeof...(Args) - 1 - I>(NGS_PP_PERFECT_FORWARD(t)); }

#if defined(__cpp_deduction_guides)
	template<class... Args>
	static_tuple(Args&&...) -> static_tuple<Args...>;
#endif
}

using static_tuple_adl::static_tuple;

constexpr decltype(auto) make_tuple(auto&&... args)
{
	return static_tuple<::std::decay_t<decltype(args)...>>(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END