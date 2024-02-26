#pragma once

#include "./defined.h"

NGS_STATIC_STRING_BEGIN

template<class T>
concept static_string = requires{
	typename type_traits::object_t<T>::value_type;
	typename type_traits::object_t<T>::traits_type;
	requires ::std::convertible_to<T, ::std::basic_string_view<typename type_traits::object_t<T>::value_type, typename type_traits::object_t<T>::traits_type>>;
};

template<std::size_t N, class CharType, class Traits = std::char_traits<CharType>>
struct basic_string {
	using value_type = CharType;
	using traits_type = Traits;

	constexpr static size_t char_size = N;

	using string_type = value_type[char_size];

	consteval explicit(false) basic_string(const value_type(&str)[N]) noexcept {
		for (size_t i = 0; i < char_size; i++)
		{
			source[i] = str[i];
		}
	}

	constexpr operator ::std::basic_string<value_type, traits_type>()const {
		return ::std::basic_string<value_type, traits_type>(source);
	}
	constexpr operator ::std::basic_string_view<value_type, traits_type>()const
	{
		return ::std::basic_string_view<value_type, traits_type>(source,char_size);
	}

	constexpr auto&& data() { return source; }
	constexpr auto&& data()const { return source; }

	constexpr size_t size()const { return char_size; }

	string_type source{};
};

template<std::size_t _N>
using string = basic_string<_N, char>;
template<std::size_t _N>
using wstring = basic_string<_N, wchar_t>;
template<std::size_t _N>
using u16string = basic_string<_N, char16_t>;
template<std::size_t _N>
using u32string = basic_string<_N, char32_t>;
template<std::size_t _N>
using u8string = basic_string<_N, char8_t>;

NGS_STATIC_STRING_END
