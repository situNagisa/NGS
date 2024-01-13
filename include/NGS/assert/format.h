#pragma once

#include "./defined.h"

NGS_ASSERT_BEGIN

inline decltype(auto) assert_format(
	std::string_view expression, std::string_view message
)
{
	return to_strings::format(
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
	return assert_format(expression, message) + to_strings::format(
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

NGS_ASSERT_END