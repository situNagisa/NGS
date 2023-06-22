#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"

NGS_BEGIN

template<typename T, typename Arg>
inline constexpr auto&& any_cast(const Arg& arg) {
	return const_cast<T>(*reinterpret_cast<const T*>(&arg));
}
inline std::string GetFunctionName(const std::string& function) {
	std::regex function_name(R"(\b((<\s*)?[a-zA-Z_]\w*(\s*>)?\s*::\s*)*[a-zA-Z_]\w*\s*(\(\))?(?=\([^()]*\)))");
	std::smatch match;
	if (std::regex_search(function, match, function_name)) {
		return match[0].str();
	}
	return {};
}

NGS_END