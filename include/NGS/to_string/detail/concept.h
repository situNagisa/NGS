#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class Char>
concept string = ::std::ranges::input_range<T> && ::std::same_as<::std::ranges::range_value_t<T>, Char>;

namespace _detail
{
	template<class T, class Char>
	concept member_stringable = requires(T t) { { NGS_PP_PERFECT_FORWARD(t).to_string() } -> string<Char>; };

	template<class T, class Char>
	concept adl_stringable = requires(T t) { { to_string(NGS_PP_PERFECT_FORWARD(t)) } -> string<Char>; };

	template<class T, class Char>
	concept stl_stringable = requires(T t) { { ::std::to_string(NGS_PP_PERFECT_FORWARD(t)) } -> string<Char>; };

	enum class to_string_policy
	{
		identity,
		construct,
		convert,
		member,
		adl,
		stl,
		none,
	};

	template<class T, class Char, string<Char> String>
	constexpr auto choice()
	{
		using char_type = Char;

		if constexpr (string<T, Char>)
		{
			return to_string_policy::identity;
		}
		else if constexpr (::std::constructible_from<String, T>) 
		{
			return to_string_policy::construct;
		}
		else if constexpr (::std::convertible_to<T, String>)
		{
			return to_string_policy::convert;
		}
		else if constexpr (member_stringable<T, char_type>)
		{
			return to_string_policy::member;
		}
		else if constexpr (adl_stringable<T, char_type>)
		{
			return to_string_policy::adl;
		}
		else if constexpr (stl_stringable<T, char_type>)
		{
			return to_string_policy::stl;
		}
		else
		{
			return to_string_policy::none;
		}
	}

	template<class T, class Char, class String>
	concept policy_stringable = string<String, Char> && _detail::choice<T, Char, String>() != to_string_policy::none;
}

template<class T, class Char, class String>
concept basic_stringable = _detail::policy_stringable<T,Char, String>;

namespace _detail
{
	template<class T, class String>
	concept stl_basic_stringable = basic_stringable<T, ::std::ranges::range_value_t<String>, String>;
}

template<class T>
concept stringable = _detail::stl_basic_stringable<T, ::std::string>;

template<class T>
concept wstringable = _detail::stl_basic_stringable<T, ::std::wstring>;

#ifdef __cpp_lib_char8_t
template<class T>
concept u8stringable = _detail::stl_basic_stringable<T, ::std::u8string>;
#endif

template<class T>
concept u16stringable = _detail::stl_basic_stringable<T, ::std::u16string>;

template<class T>
concept u32stringable = _detail::stl_basic_stringable<T, ::std::u32string>;


template<class T>
concept view_stringable = _detail::stl_basic_stringable<T, ::std::string_view>;

template<class T>
concept wview_stringable = _detail::stl_basic_stringable<T, ::std::wstring_view>;

#ifdef __cpp_lib_char8_t
template<class T>
concept u8view_stringable = _detail::stl_basic_stringable<T, ::std::u8string_view>;
#endif

template<class T>
concept u16view_stringable = _detail::stl_basic_stringable<T, ::std::u16string_view>;

template<class T>
concept u32view_stringable = _detail::stl_basic_stringable<T, ::std::u32string_view>;

NGS_LIB_MODULE_END