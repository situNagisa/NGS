#pragma once

#include "../defined.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template<class _T>
concept is_param = cpt::any<_T>;

NGS_STATIC_FUNCTIONAL_END