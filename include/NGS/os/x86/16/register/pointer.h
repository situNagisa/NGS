#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//sp
struct stack_pointer_register : trivial_register<registers::sp> {};
//bp
struct base_pointer_register : trivial_register<registers::bp> {};

NGS_LIB_MODULE_END