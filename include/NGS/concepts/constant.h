#pragma once

#include "NGS/concepts/defined.h"

NGS_CCPT_BEGIN

template<class T = void>
concept Constant = requires() {
	typename T::value_type;
	{ T::value } -> std::convertible_to<typename T::value_type>;
};

NGS_CCPT_END
