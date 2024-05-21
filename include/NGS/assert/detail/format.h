#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
inline decltype(auto) assert_format(
	::std::string_view expression, ::std::string_view message
)
{
#if NGS_ASSERT_CONFIG_FORMAT_ENABLE
	return fmt::c(
		""
		"\nerror:: %s"
		"\nassert  : %s",
		message.data(),
		expression.data()
	);
#else
	return
		"\nerror::unknown"
		"\nassert	: unknown"
		;
#endif
}
inline decltype(auto) assert_format(
	::std::string_view expression, ::std::string_view message,
	const locations::source_location& location
)
{
	return
#if NGS_ASSERT_CONFIG_FORMAT_ENABLE
		assert_format(expression, message) +
		fmt::c(
			""
			"\nfunction: %s"
			"\nfile    : %s"
			"\nline %d,column %d",
			location.function_name(),
			location.file_name(),
			location.line(),
			location.column()
		);
#else
		"\nerror::unknown"
		"\nassert	: unknown"
		"\nfunction: unknown"
		"\nfile    : " __FILE__
		"\nline unknown,column unknown";
#endif
}

inline decltype(auto) print_assert(::std::string_view message)
{
#if NGS_ASSERT_CONFIG_LOG_ENABLE
	logs::std_logger.print_line(
		consoles::text_color::red,
		"\n=========================",
		message,
		"\n=========================",
		consoles::text_color::reset
	);
#endif
}
NGS_LIB_MODULE_END