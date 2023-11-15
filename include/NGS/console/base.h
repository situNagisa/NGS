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

#if defined(NGS_USE_HPP)
#	include "./impl.h"
#endif
