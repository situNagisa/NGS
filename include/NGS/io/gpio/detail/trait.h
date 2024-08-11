#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class level : bool
{
	low = false,
	high = true,
};

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(set, (::std::convertible_to<level>));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(pin_level);

NGS_LIB_MODULE_END