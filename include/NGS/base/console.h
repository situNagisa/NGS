#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

class Console {
public:
	enum class Color {
		RESERT,
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};
public:

	static void SetTextColor(Color);
	static void SetBackgroundColor(Color);
private:

private:

};

NGS_END
