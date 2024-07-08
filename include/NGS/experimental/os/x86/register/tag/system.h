#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t BitSize>
struct system : basic_register<BitSize>
{
	NGS_PP_INJECT(system);
};

NGS_OS_X86_REGISTER(system);

struct gdtr : system<48> {};
struct ldtr : system<16> {};
struct idtr : system<48> {};

NGS_LIB_MODULE_END