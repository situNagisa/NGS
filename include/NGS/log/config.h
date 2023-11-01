#pragma once

#include "./defined.h"
#include "./level.h"

NGS_LOG_BEGIN

struct NGS_DLL_API logger_config
{
	std::unordered_map<log_level, consoles::text_color> level_colors = {
		{log_level::trace,consoles::text_color::cyan},
		{log_level::debug,consoles::text_color::green},
		{log_level::info,consoles::text_color::white},
		{log_level::warn,consoles::text_color::yellow},
		{log_level::error,consoles::text_color::red},
		{log_level::fatal,consoles::text_color::red},
	};
	struct
	{
		bool scope_name : 1 = true;
		bool time : 1 = false;
	}enable_print;
};

NGS_LOG_END