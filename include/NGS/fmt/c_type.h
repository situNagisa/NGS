#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

inline ::std::string c(::std::string_view f, ...) {
	::std::string buffer{};

	va_list args;
	va_start(args, f);
	size_t buffer_size = ::std::vsnprintf(nullptr, 0, f.data(), args);
	buffer.resize(buffer_size);
	::std::vsnprintf(buffer.data(), buffer_size + 1, f.data(), args);
	va_end(args);
	return buffer;
}

NGS_LIB_END