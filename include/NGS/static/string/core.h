#pragma once

#include "./defined.h"

NGS_STATIC_STRING_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CString = requires(_ObjectType obj, const _ObjectType obj_cst) {
	typename _ObjectType::value_type;
	typename _ObjectType::traits_type;
	{ _ObjectType::size }->std::convertible_to<std::size_t>;
	{ obj_cst.data() }->std::convertible_to<const typename _ObjectType::value_type*>;
};

template<std::size_t _N, class _CharType, class _Traits = std::char_traits<_CharType>>
struct basic_string {
	using value_type = _CharType;
	using traits_type = _Traits;

	constexpr static size_t char_size = _N;

	using string_type = value_type[char_size];

	consteval explicit(false) basic_string(const value_type(&str)[_N]) noexcept {
		for (size_t i = 0; i < char_size; i++)
		{
			source[i] = str[i];
		}
	}

	constexpr operator std::basic_string<value_type, traits_type>()const {
		return std::basic_string<value_type, traits_type>(source);
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
