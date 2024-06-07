#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	consteval void constant_evaluated_expression(auto&&){}

	template<class T,::std::size_t S>
	constexpr ::std::integral_constant<::std::size_t, S> derived_from_array(const ::std::array<T, S>&);

	template<class T, ::std::size_t S>
	constexpr ::std::integral_constant<::std::size_t, S> derived_from_span(const ::std::span<T, S>&);

	enum class choose_t
	{
		none,
		array,
		std_array,
		std_span,
		static_size,
		size,
	};

	template<class T>
	consteval choose_t choose()
	{
		if constexpr (::std::is_array_v<T>)
		{
			return choose_t::array;
		}
		else if constexpr (requires(T t) { _detail::derived_from_array(t); })
		{
			return choose_t::std_array;
		}
		else if constexpr (requires(T t)
		{
			_detail::derived_from_span(t);
			requires decltype(_detail::derived_from_span(::std::declval<T>()))::value != ::std::dynamic_extent;
		})
		{
			return choose_t::std_span;
		}
		else if constexpr (requires{ { T::static_size() } -> ::std::convertible_to<::std::size_t>; })
		{
			return choose_t::static_size;
		}
		else if constexpr (requires{ { T::size() } -> ::std::convertible_to<::std::size_t>; })
		{
			return choose_t::size;
		}
		else
		{
			return choose_t::none;
		}
	}


	template<::std::ranges::sized_range T>
	struct static_size_functor
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR consteval decltype(auto) operator()() NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
			requires (_detail::choose<T>() != choose_t::none)
		{
			constexpr auto choose_v = _detail::choose<T>();
			/*if constexpr (::std::default_initializable<T> && requires { _detail::constant_evaluated_expression(T{}); })
			{
				return ::std::ranges::size(T{});
			}
			else */if constexpr (choose_v == choose_t::array)
			{
				return ::std::extent_v<T>;
			}
			else if constexpr (choose_v == choose_t::std_array)
			{
				using t = decltype(_detail::derived_from_array(::std::declval<T>()));
				return t::value;
			}
			else if constexpr (choose_v == choose_t::std_span)
			{
				using t = decltype(_detail::derived_from_span(::std::declval<T>()));
				return t::value;
			}
			else if constexpr (choose_v == choose_t::static_size)
			{
				return T::static_size();
			}
			else if constexpr (choose_v == choose_t::size)
			{
				return T::size();
			}
			else
			{
				static_assert(cpt::none<T>);
			}
		}
	};
}

template<::std::ranges::sized_range T>
inline constexpr _detail::static_size_functor<T> static_size{};

template<class T>
concept static_sized_range = ::std::ranges::sized_range<T> && requires { static_size<T>(); };

NGS_LIB_MODULE_END