#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

inline decltype(auto) assert_format(
	std::string_view expression, std::string_view message
)
{
	return fmt::c(
		""
		"\nerror:: %s"
		"\nassert  : %s",
		message.data(),
		expression.data()
	);
}
inline decltype(auto) assert_format(
	std::string_view expression, std::string_view message,
	const locations::source_location& location
)
{
	return assert_format(expression, message) + fmt::c(
		""
		"\nfunction: %s"
		"\nfile    : %s"
		"\nline %d,column %d",
		location.function_name(),
		location.file_name(),
		location.line(),
		location.column()
	);
}

inline decltype(auto) print_assert(std::string_view message)
{
	logs::std_logger.print_line(
		consoles::text_color::red,
		"\n=========================",
		message,
		"\n=========================",
		consoles::text_color::reset
	);
}

NGS_LIB_END