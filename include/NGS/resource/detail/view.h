#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<resource R>
struct ref_view
{
	NGS_PP_INJECT_BEGIN(ref_view);
public:
	using resource_type = R;

	constexpr static void _test(resource_type&){}
	constexpr static void _test(resource_type&&) = delete;

	template<class T>
		requires (!::std::same_as<::std::remove_cvref_t<T>, ref_view>) && ::std::convertible_to<T, resource_type&>&& requires{ self_type::_test(::std::declval<T>()); }
	constexpr explicit(false) ref_view(T&& t)
		: _data(::std::addressof(NGS_PP_PERFECT_FORWARD(t)))
	{

	}

	constexpr auto&& base() const { return *_data; }

	constexpr explicit(true) operator resource_type& () const { return *_data; }

	resource_type* _data;
};

template<class R>
ref_view(R&) -> ref_view<R>;

template<resource R>
struct owning_view
{
	NGS_PP_INJECT_BEGIN(owning_view);
public:
	using resource_type = R;

	constexpr owning_view() requires ::std::default_initializable<resource_type> = default;
	constexpr owning_view(self_type&&) = default;
	constexpr explicit(false) owning_view(resource_type&& data)
		: _data(::std::move(data))
	{
		
	}
	constexpr owning_view(const self_type&) = delete;

	constexpr self_type& operator=(self_type&& other) = default;
	constexpr self_type& operator=(const self_type&) = delete;

	constexpr auto&& base() & noexcept { return _data; }
	constexpr auto&& base() const & noexcept { return _data; }
	constexpr auto&& base() && noexcept { return ::std::move(_data); }
	constexpr auto&& base() const && noexcept { return ::std::move(_data); }

	constexpr explicit(true) operator resource_type& () const { return *_data; }

	resource_type _data;
};

inline constexpr struct gain_cpo
{
	enum class state
	{
		none,
		view,
		reference,
		own,
	};
	template<class R>
	constexpr static auto choose() noexcept
	{
		if constexpr (view<::std::remove_cvref_t<R>>)
		{
			if constexpr(::std::convertible_to<R, ::std::remove_cvref_t<R>>)
			{
				return state::view;
			}
		}
		else if constexpr (requires(R && e) { ref_view{ NGS_PP_PERFECT_FORWARD(e) }; })
		{
			return state::reference;
		}
		else if constexpr (requires(R && e) { owning_view{ NGS_PP_PERFECT_FORWARD(e) }; })
		{
			return state::own;
		}
		return state::none;
	}

	template<class R>
	constexpr static auto choice = choose<R>();

	template<class R>
		requires (choice<R> != state::none)
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(R&& e) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (choice<R> == state::view)
		{
			return NGS_PP_PERFECT_FORWARD(e);
		}
		else if constexpr (choice<R> == state::reference)
		{
			return ref_view{ NGS_PP_PERFECT_FORWARD(e) };
		}
		else if constexpr (choice<R> == state::own)
		{
			return owning_view{ NGS_PP_PERFECT_FORWARD(e) };
		}
	}
}gain{};

template<viewable_resource T>
using gain_t = decltype(gain(::std::declval<T>()));

NGS_LIB_MODULE_END