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
};

NGS_LOG_END

NGS_TOSTRING_BEGIN

NGS_CONSTEXPR17 std::string_view to_string(logs::log_level level)
{
	switch (level)
	{
	case logs::log_level::trace: return "trace";
	case logs::log_level::debug: return "debug";
	case logs::log_level::info: return "info";
	case logs::log_level::warn: return "warn";
	case logs::log_level::error: return "error";
	case logs::log_level::fatal: return "fatal";
	default: return "unknown";
	}
}

NGS_TOSTRING_END