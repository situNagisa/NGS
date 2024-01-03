#pragma once

#include "./concept.h"

NGS_BEGIN

constexpr ::std::string to_string(const math::vectors::input_vector auto& v)
{
	::std::string result{};
	result += "{";
	for (auto i = ::std::ranges::begin(v); i != ::std::ranges::end(v); ++i)
	{
		result += ::ngs::to_string(*i);
		result += ", ";
	}
	result += "}";
	return result;
}

NGS_END