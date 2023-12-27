#pragma once

#include "./concept.h"

NGS_TOSTRING_BEGIN

constexpr ::std::string to_string(const math::vectors::input_vector auto& v)
{
	::std::string result{};
	for (auto i = ::std::ranges::begin(v); i != ::std::ranges::end(v); ++i)
	{
		result += ::ngs::to_string(*i);
		if (i != ::std::ranges::end(v) - 1)
		{
			result += ", ";
		}
	}
	return result;
}

NGS_TOSTRING_END