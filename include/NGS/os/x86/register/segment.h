#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct segment : basic_register<BitSize>
{
	NGS_PP_INJECT(segment);
};

NGS_OS_X86_REGISTER(segment);

struct cs : segment<16> {};
struct ds : segment<16> {};
struct es : segment<16> {};
struct fs : segment<16> {};
struct gs : segment<16> {};
struct ss : segment<16> {};

NGS_LIB_MODULE_END