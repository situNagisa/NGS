#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

template<_CPT Function Fn>
bool operator==(const std::function<Fn>& a, const std::function<Fn>& b) {
	return *(a.template target<Fn>()) == *(b.template target<Fn>());
}

NGS_END