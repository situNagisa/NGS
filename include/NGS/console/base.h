#pragma once

#include "./defined.h"

NGS_CONSOLE_BEGIN

enum class text_color
{
	reset,
	black,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white,
};

struct NGS_DLL_API console
{

	console(int count, ...);
	~console();

	void set_text_color(text_color front, text_color back = text_color::black);

private:
	void_ptr _data = nullptr;
};



NGS_CONSOLE_END

#if NGS_SYSTEM_IS_WINDOWS
#	include "./impl/windows.hpp"
#elif NGS_SYSTEM_IS_LINUX
#	include "./impl/linux.hpp"
#elif NGS_SYSTEM_IS_MAC
#	include "./impl/mac.hpp"
#else
#	include "./impl/none.hpp"
#endif
