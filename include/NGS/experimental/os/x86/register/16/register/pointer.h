#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//sp
struct stack_pointer_register : trivial_register<tags::sp> {};
//bp
struct base_pointer_register : trivial_register<tags::bp> {};

NGS_LIB_MODULE_END