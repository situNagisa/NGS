#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

inline ::std::string format(std::string_view fmt, ...) {
	::std::string buffer{};

	va_list args;
	va_start(args, fmt);
	size_t buffer_size = vsnprintf(nullptr, 0, fmt.data(), args);
	buffer.resize(buffer_size);
	vsnprintf(buffer.data(), buffer_size + 1, fmt.data(), args);
	va_end(args);
	return buffer;
}


NGS_LIB_END