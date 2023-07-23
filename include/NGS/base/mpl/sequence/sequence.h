#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl_macro.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(sequence, class...);

NGS_mfunction(push_back, class, class...);
NGS_mfunction(push_back, class... _Element, class... _Args) < sequence<_Args...>, _Element... > {
	NGS_mreturn_t sequence<_Args..., _Element...>;
};
NGS_mfunction(push_front, class, class...);
NGS_mfunction(push_front, class... _Element, class... _Args) < sequence<_Args...>, _Element... > {
	NGS_mreturn_t sequence<_Element..., _Args...>;
};

NGS_END
NGS_END
