#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct control : basic_register<BitSize>
{
	NGS_PP_INJECT(control);
};

NGS_OS_X86_REGISTER(control);

struct cr0 : control<32> {};
struct cr1 : control<32> {};
struct cr2 : control<32> {};
struct cr3 : control<32> {};
struct cr4 : control<32> {};

NGS_LIB_MODULE_END