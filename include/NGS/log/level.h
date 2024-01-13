#pragma once

#include "./defined.h"

NGS_LOG_BEGIN

enum class log_level
{
	trace,
	debug,
	info,
	warn,
	error,
	fatal,
	max,
};

NGS_CONSTEXPR17 std::string_view to_string(log_level level)
{
	switch (level)
	{
	case log_level::trace: return "trace";
	case log_level::debug: return "debug";
	case log_level::info: return "info";
	case log_level::warn: return "warn";
	case log_level::error: return "error";
	case log_level::fatal: return "fatal";
	default: return "unknown";
	}
}

NGS_LOG_END