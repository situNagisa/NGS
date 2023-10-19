#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

template<class _Type>
constexpr std::string to_string_by_stream(_Type& value)
	requires
	requires(std::stringstream s) { s << value; }
{
	std::stringstream s{};
	s << value;
	return s.str();
}

constexpr std::string to_string(char c) {
	return std::string(1, c);
}

template<class _Type>
constexpr std::string to_string(_Type&& value)
	requires
	requires{ std::string(value); } ||
	requires{ std::to_string(value); }
{
	if constexpr (requires{
		std::string(value);
	}) {
		return std::string(value);
	}
	else if constexpr (requires{
		std::to_string(value);
	}) {
		return std::to_string(value);
	}
	else {
		static_assert(ccpt::None<_Type>, "to_string not implemented for this type");
	}
}

template<class _T, class _Type>
std::basic_ostream<std::string::value_type, _T>& operator<< (std::basic_ostream<std::string::value_type, _T>& os, _Type&& value)
	requires
	requires{ to_string(value); } &&
(!std::convertible_to<_Type, std::string>)
{
	os << to_string(value);
	return os;
}

NGS_END
