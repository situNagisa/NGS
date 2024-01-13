#pragma once

#include "./concept.h"

NGS_LIB_BEGIN
namespace io
{
	struct allow_adl_io : bases::empty {};

	constexpr ::std::string to_string(const input_vector auto& v)
	{
		using sentinel_type = ::std::ranges::sentinel_t<decltype(v)>;

		::std::string result{};
		result += "{";
		if constexpr (!adapter_vector<decltype(v)>)
		{
			for (auto i = ::std::ranges::begin(v); i != ::std::ranges::end(v); ++i)
			{
				result += to_strings::to_string(*i);
				if constexpr (::std::random_access_iterator<sentinel_type>)
				{
					if (i != ::std::ranges::end(v) - 1)
						result += ", ";
				}
				else
				{
					result += ", ";
				}

			}
		}
		else
		{
			result += "a:";
			result += to_strings::to_string(*::std::ranges::begin(v));
		}

		result += "}";
		return result;
	}
}
using io::allow_adl_io;
using io::to_string;

NGS_LIB_END