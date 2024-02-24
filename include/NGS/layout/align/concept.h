#pragma once

#include "./constant.h"
#include "./valid_align.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Align, align_t DefaultAlign = 1>
concept align = ccpt::constant<Align,align_t> && NGS_LIB_MODULE_NAME::is_valid_align(type_traits::object_t<Align>::value, DefaultAlign);

NGS_LIB_MODULE_END
