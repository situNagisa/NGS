#pragma once

#include "./constant.h"
#include "./valid_align.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t Align> requires (NGS_LIB_MODULE_NAME::is_valid_align(align_t(Align)))
struct normal_align : align_constant<Align,Align> {};

NGS_LIB_MODULE_END