#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::pin_t;
namespace literals
{
	using details::operator ""_pin;
}

NGS_LIB_END