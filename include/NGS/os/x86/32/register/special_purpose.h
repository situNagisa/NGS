#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ip
struct instruction_pointer_register : extend_trivial_register<bit16::instruction_pointer_register, registers::eip> {};

NGS_LIB_MODULE_END