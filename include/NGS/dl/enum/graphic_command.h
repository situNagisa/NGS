#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

enum class NGS_API GraphicPathCommand {
	point,
	circle,
	ellipse,
	rectangle,
	rectangle_round_circle,
	rectangle_round_ellipse,
	color,
	broken_line,
	polygon,
};

NGS_DL_END
