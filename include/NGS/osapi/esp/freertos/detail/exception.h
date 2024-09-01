#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct esp_exception : ::std::runtime_error
{
	explicit esp_exception(::esp_err_t error_code, ::std::string_view what_arg)
		: ::std::runtime_error(::std::format("code: {:#04x}, message: {}", error_code, what_arg))
	{}
};

NGS_LIB_MODULE_END