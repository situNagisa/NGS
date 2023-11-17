#pragma once

#include "./defined.h"

NGS_TOSTRING_BEGIN

namespace detail
{


	enum class to_string_type
	{
		operator_string,
		stream,
		std_to_string,
		none,
	};
	template<class _T>
	constexpr to_string_type choice()
	{
		if constexpr (requires(_T t) { std::string(t); }) {
			return to_string_type::operator_string;
		}
		else if constexpr (requires(std::stringstream s, _T t) { std::operator<<(s, t); }) {
			return to_string_type::stream;
		}
		else if constexpr (requires(_T t) { std::to_string(t); }) {
			return to_string_type::std_to_string;
		}
		else
		{
			return to_string_type::none;
		}
	}

}

NGS_TOSTRING_STRING_CONSTEXPR std::string to_string(auto&& target)
	requires (to_strings::detail::choice<decltype(target)>() == to_strings::detail::to_string_type::operator_string)
{
	return std::string(NGS_PP_PERFECT_FORWARD(target));
}

NGS_TOSTRING_STRING_CONSTEXPR std::string to_string(auto&& target)
	requires (to_strings::detail::choice<decltype(target)>() == to_strings::detail::to_string_type::stream)
{
	std::stringstream s{};
	s << NGS_PP_PERFECT_FORWARD(target);
	return s.str();
}

NGS_TOSTRING_STRING_CONSTEXPR std::string to_string(auto&& target)
	requires (to_strings::detail::choice<decltype(target)>() == to_strings::detail::to_string_type::std_to_string)
{
	return std::to_string(NGS_PP_PERFECT_FORWARD(target));
}

NGS_TOSTRING_STRING_CONSTEXPR std::string to_string(char c) { return { 1,c }; }
NGS_CONSTEXPR20 std::string_view to_string(bool c) { return c ? "true" : "false"; }

template<class _T>
std::basic_ostream<std::string::value_type, _T>& operator<< (std::basic_ostream<std::string::value_type, _T>& os, auto&& target)
	requires (to_strings::detail::choice<decltype(target)>() == to_strings::detail::to_string_type::none) && requires{ ngs::to_string(NGS_PP_PERFECT_FORWARD(target)); }
{
	os << ngs::to_string(NGS_PP_PERFECT_FORWARD(target));
	return os;
}

NGS_TOSTRING_END
