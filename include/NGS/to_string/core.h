#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	void to_string();

	enum class to_string_type
	{
		conversion,
		member,
		adl,
		stl,
		stl_stream,
		adl_stream,
		none,
	};

	template<class _T>
	concept conversion_stringable = requires(_T t) { std::string(NGS_PP_PERFECT_FORWARD(t)); };

	template<class _T>
	concept member_stringable = requires(_T t) { {NGS_PP_PERFECT_FORWARD(t).to_string()}; };

	template<class _T>
	concept adl_searchable = requires(_T t) { { to_string(NGS_PP_PERFECT_FORWARD(t)) }; };

	template<class _T>
	concept stl_stringable = requires(_T t) { ::std::to_string(NGS_PP_PERFECT_FORWARD(t)); };

	template<class _Stream, class _T>
	concept stl_streamable = requires(_Stream s, _T t) { ::std::operator<<(s, NGS_PP_PERFECT_FORWARD(t)); };

	template<class _Stream, class _T>
	concept adl_streamable = requires(_Stream s, _T t) { s << NGS_PP_PERFECT_FORWARD(t); };

	template<class _T>
	constexpr to_string_type choice()
	{
		if constexpr (conversion_stringable<_T>) {
			return to_string_type::conversion;
		}
		else if constexpr (member_stringable<_T>)
		{
			return to_string_type::member;
		}
		else if constexpr (adl_searchable<_T>)
		{
			return to_string_type::adl;
		}
		else if constexpr (stl_stringable<_T>) {
			return to_string_type::stl;
		}
		else if constexpr (stl_streamable<::std::stringstream, _T>) {
			return to_string_type::stl_stream;
		}
		else if constexpr (adl_streamable<::std::stringstream, _T>)
		{
			return to_string_type::adl_stream;
		}
		else
		{
			return to_string_type::none;
		}
	}

}

inline constexpr struct
{
	NGS_TOSTRING_STRING_CONSTEXPR decltype(auto) operator()(auto&& target)const
		requires (detail::choice<decltype(target)>() != detail::to_string_type::none)
	{
		constexpr auto choice = detail::choice<decltype(target)>();
		if constexpr (choice == detail::to_string_type::conversion)
		{
			return std::string(NGS_PP_PERFECT_FORWARD(target));
		}
		else if constexpr (choice == detail::to_string_type::member)
		{
			return NGS_PP_PERFECT_FORWARD(target).to_string();
		}
		else if constexpr (choice == detail::to_string_type::adl)
		{
			return to_string(NGS_PP_PERFECT_FORWARD(target));
		}
		else if constexpr (choice == detail::to_string_type::stl)
		{
			return ::std::to_string(NGS_PP_PERFECT_FORWARD(target));
		}
		else if constexpr (choice == detail::to_string_type::stl_stream)
		{
			std::stringstream s{};
			::std::operator<<(s, NGS_PP_PERFECT_FORWARD(target));
			return s.str();
		}
		else if constexpr (choice == detail::to_string_type::adl_stream)
		{
			std::stringstream s{};
			s << NGS_PP_PERFECT_FORWARD(target);
			return s.str();
		}
		else
		{
			return std::string{};
		}
	}
	NGS_TOSTRING_STRING_CONSTEXPR::std::string operator()(char c)const
	{
		return { 1,c };
	}
	NGS_CONSTEXPR20::std::string_view operator()(bool c)const
	{
		return c ? "true" : "false";
	}
}to_string{};

NGS_LIB_END

template<class _T>
::std::basic_ostream<std::string::value_type, _T>& operator<< (::std::basic_ostream<std::string::value_type, _T>& os, auto&& target)
	requires !NGS_NS::NGS_LIB_NAME::detail::stl_streamable<::std::basic_ostream<std::string::value_type, _T>, decltype(target)>&&
	requires { NGS_NS::NGS_LIB_NAME::to_string(NGS_PP_PERFECT_FORWARD(target)); }
{
	os << NGS_NS::NGS_LIB_NAME::to_string(NGS_PP_PERFECT_FORWARD(target));
	return os;
}