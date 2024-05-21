#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct pointer : basic_register<BitSize>
{
	NGS_PP_INJECT(pointer);
};

NGS_OS_X86_REGISTER(pointer);

struct sp : pointer<16> {};
struct esp : pointer<32> {};

struct bp : pointer<16> {};
struct ebp : pointer<32> {};

NGS_LIB_MODULE_END