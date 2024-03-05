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

	template<class T>
	concept conversion_stringable = requires(T t) { std::string(NGS_PP_PERFECT_FORWARD(t)); };

	template<class T>
	concept member_stringable = requires(T t) { {NGS_PP_PERFECT_FORWARD(t).to_string()}; };

	template<class T>
	concept adl_searchable = requires(T t) { { to_string(NGS_PP_PERFECT_FORWARD(t)) }; };

	template<class T>
	concept stl_stringable = requires(T t) { ::std::to_string(NGS_PP_PERFECT_FORWARD(t)); };

	template<class Stream, class T>
	concept stl_streamable = requires(Stream s, T t) { ::std::operator<<(s, NGS_PP_PERFECT_FORWARD(t)); };

	template<class Stream, class T>
	concept adl_streamable = requires(Stream s, T t) { s << NGS_PP_PERFECT_FORWARD(t); };

	template<class T>
	constexpr to_string_type choice()
	{
		if constexpr (conversion_stringable<T>) {
			return to_string_type::conversion;
		}
		else if constexpr (member_stringable<T>)
		{
			return to_string_type::member;
		}
		else if constexpr (adl_searchable<T>)
		{
			return to_string_type::adl;
		}
		else if constexpr (stl_stringable<T>) {
			return to_string_type::stl;
		}
		else if constexpr (stl_streamable<::std::stringstream, T>) {
			return to_string_type::stl_stream;
		}
		else if constexpr (adl_streamable<::std::stringstream, T>)
		{
			return to_string_type::adl_stream;
		}
		else
		{
			return to_string_type::none;
		}
	}

	template<class T>
	concept policy_stringable = detail::choice<T>() != to_string_type::none;


	template<class T>
	concept fundamental_array = ::std::is_array_v<type_traits::naked_t<T>> && cpt::fundamental<::std::remove_all_extents_t<type_traits::naked_t<T>>>;

	template<class T>
	concept default_stringable = ::std::convertible_to<T,bool> || ::std::convertible_to<T,char> || fundamental_array<T>;
}

template<class T>
concept stringable = detail::policy_stringable<T> || detail::default_stringable<T>;

inline constexpr struct
{
	NGS_TOSTRING_STRING_CONSTEXPR decltype(auto) operator()(detail::policy_stringable auto&& target)const
		requires !detail::fundamental_array<decltype(target)>
	{
		constexpr auto choice = detail::choice<decltype(target)>();
		if constexpr (choice == detail::to_string_type::conversion)
		{
			return ::std::string(NGS_PP_PERFECT_FORWARD(target));
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
			::std::stringstream s{};
			::std::operator<<(s, NGS_PP_PERFECT_FORWARD(target));
			return s.str();
		}
		else if constexpr (choice == detail::to_string_type::adl_stream)
		{
			::std::stringstream s{};
			s << NGS_PP_PERFECT_FORWARD(target);
			return s.str();
		}
		else
		{
			return ::std::string{};
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
	NGS_TOSTRING_STRING_CONSTEXPR::std::string operator()(detail::fundamental_array auto&& range)const
	{
		::std::string result{};
		result += "{";
		for (auto i = ::std::ranges::begin(range); i != ::std::ranges::end(range); ++i)
		{
			result += (i == ::std::ranges::begin(range) ? "" : ", ") + (*this)(*i);
		}
		result += "}";
		return result;
	}
}to_string{};

NGS_LIB_END

template<class T>
::std::basic_ostream<::std::string::value_type, T>& operator<< (::std::basic_ostream<::std::string::value_type, T>& os, auto&& target)
	requires	!NGS_NS::NGS_LIB_NAME::detail::stl_streamable<::std::basic_ostream<::std::string::value_type, T>, decltype(target)>&&
				!NGS_NS::NGS_LIB_NAME::detail::adl_streamable<::std::basic_ostream<::std::string::value_type, T>, decltype(target)>&&
				NGS_NS::NGS_LIB_NAME::stringable<decltype(target)>
{
	os << NGS_NS::NGS_LIB_NAME::to_string(NGS_PP_PERFECT_FORWARD(target));
	return os;
}