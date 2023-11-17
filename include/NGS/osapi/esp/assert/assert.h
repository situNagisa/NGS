#pragma once

#include "./defined.h"

NGS_OS_ESP_ASSERT_BEGIN

inline bool check_error(
	esp_err_t code,
	std::string_view expression,
	std::string_view message = "",
	const locations::source_location& location = locations::source_location::current()
)
{
	if (code == ESP_OK)
		return true;

	std::string info{};
	info += esp_err_to_name(code);
	info += " : ";
	info += message;

	ngs::asserts::print_assert(ngs::asserts::assert_format(expression, info, location));

	return false;
}

NGS_OS_ESP_ASSERT_END

#if defined(NGS_BUILD_TYPE_IS_DEBUG)

#	define NGS_OS_ESP_EXPECT_ERROR(error,...) NGS_ os_api::esp::asserts::check_error(error,#error NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__))
#	define NGS_OS_ESP_ASSERT_ERROR(error,...)			\
do														\
{														\
	if (!NGS_OS_ESP_EXPECT_ERROR(error, __VA_ARGS__))	\
		while (true) ;									\
} while (false)											\
//

#else

#	define NGS_OS_ESP_ASSERT_ERROR(error,...) (error)
#	define NGS_OS_ESP_EXPECT_ERROR(error,...) (error)

#endif