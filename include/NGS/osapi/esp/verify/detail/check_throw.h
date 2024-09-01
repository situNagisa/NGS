#pragma once

#include "./exception.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

#define NGS_ASSERT_FAIL() while(true)

#ifdef __cpp_exceptions
#define NGS_OSAPI_ESP_CHECK_ASSERT_THROW(condition, exception) do{ if (!(condition)) { throw exception; } } while(false)
#else
#define NGS_OSAPI_ESP_CHECK_ASSERT_THROW(condition, exception) NGS_ASSERT((condition), (exception).what())
#endif

#define NGS_OSAPI_ESP_CHECK_ASSERT_THROW_MESSAGE(condition, message) \
	NGS_OSAPI_ESP_CHECK_ASSERT_THROW(condition, ::std::runtime_error(message))

#define NGS_OSAPI_ESP_CHECK_ERROR_THROW(error_code, exception)	NGS_OSAPI_ESP_CHECK_ASSERT_THROW((error_code) == ESP_OK, (exception))

#define NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(error_code, message)								\
do{																									\
	auto code = static_cast<::esp_err_t>(error_code);												\
	NGS_OSAPI_ESP_CHECK_ERROR_THROW(																\
		code, 																						\
		NGS_NS::NGS_OSAPI_ESP_NS::NGS_OSAPI_ESP_VERIFY_NS::details::esp_exception(code, message));	\
}while(false)																						\
//

NGS_LIB_MODULE_END