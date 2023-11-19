#pragma once

#include "./defined.h"
#include "./level.h"

NGS_LOG_BEGIN

struct NGS_DLL_API logger_config
{
	struct
	{
		std::array<consoles::text_color, static_cast<size_t>(log_level::max)> data = {
			consoles::text_color::white,
			consoles::text_color::green,
			consoles::text_color::cyan,
			consoles::text_color::yellow,
			consoles::text_color::red,
			consoles::text_color::red,
		};

		constexpr consoles::text_color operator[](log_level l) const
		{
			return data[static_cast<int>(l)];
		}
		constexpr consoles::text_color at(log_level l) const
		{
			return data.at(static_cast<int>(l));
		}

	} level_colors{};
	struct
	{
		bool scope_name : 1 = true;
		bool time : 1 = false;
	}enable_print;
};

NGS_LOG_END