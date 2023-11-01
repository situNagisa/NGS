#pragma once

#include "NGS/extend/color/defined.h"

NGS_BEGIN
NGS_CONCEPT

template <typename T>
concept CColor = requires() {
	{T::Format} -> std::convertible_to<PixelFormat>;
};

NGS_END
NGS_END
