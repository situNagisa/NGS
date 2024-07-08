#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Char, string<Char> String>
constexpr decltype(auto) convert(basic_stringable<Char, String> auto&& target)
{
	using string_type = String;
	using char_type = ::std::ranges::range_value_t<string_type>;

	constexpr auto policy = _detail::choice<decltype(target), char_type, string_type>();
	if constexpr (policy == _detail::to_string_policy::identity)
	{
		return NGS_PP_PERFECT_FORWARD(target);
	}
	else if constexpr (policy == _detail::to_string_policy::construct)
	{
		return string_type{ NGS_PP_PERFECT_FORWARD(target) };
	}
	else if constexpr (policy == _detail::to_string_policy::convert)
	{
		return static_cast<string_type>(NGS_PP_PERFECT_FORWARD(target));
	}
	else if constexpr (policy == _detail::to_string_policy::member)
	{
		return NGS_PP_PERFECT_FORWARD(target).to_string();
	}
	else if constexpr (policy == _detail::to_string_policy::adl)
	{
		return to_string(NGS_PP_PERFECT_FORWARD(target));
	}
	else if constexpr (policy == _detail::to_string_policy::stl)
	{
		return ::std::to_string(NGS_PP_PERFECT_FORWARD(target));
	}
	else
	{
		static_assert(cpt::none<string_type>);
	}
}

template<class Char, string<Char> String, string<Char> View = String>
struct basic_to_string_function
{
	using string_type = String;
	using view_type = View;
	using char_type = Char;

	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(auto&& target) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		requires basic_stringable<decltype(target), char_type, string_type> || basic_stringable<decltype(target), char_type, view_type>
	{
		if constexpr (basic_stringable<decltype(target), char_type, view_type>)
		{
			return NGS_LIB_MODULE_NAME::convert<char_type, view_type>(NGS_PP_PERFECT_FORWARD(target));
		}
		else
		{
			return NGS_LIB_MODULE_NAME::convert<char_type, string_type>(NGS_PP_PERFECT_FORWARD(target));
		}
	}
};

template<class Char, string String, string View = String>
inline constexpr basic_to_string_function<Char, String, View> basic_to_string{};

namespace _detail
{
	template<class Char>
	inline constexpr basic_to_string_function<Char, ::std::basic_string<Char>, ::std::basic_string_view<Char>> stl_basic_to_string{};
}

inline constexpr auto to_string = _detail::stl_basic_to_string<char>;

inline constexpr auto to_wstring = _detail::stl_basic_to_string<wchar_t>;

#ifdef __cpp_lib_char8_t
inline constexpr auto to_u8string = _detail::stl_basic_to_string<char8_t>;
#endif

inline constexpr auto to_u16string = _detail::stl_basic_to_string<char16_t>;

inline constexpr auto to_u32string = _detail::stl_basic_to_string<char32_t>;

NGS_LIB_MODULE_END