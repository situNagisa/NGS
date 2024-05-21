#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//sp
struct stack_pointer_register : extend_trivial_register<bit16::stack_pointer_register, registers::esp> {};
//bp
struct base_pointer_register : extend_trivial_register<bit16::base_pointer_register, registers::ebp> {};

NGS_LIB_MODULE_END