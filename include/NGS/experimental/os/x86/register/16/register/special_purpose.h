#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ip
struct instruction_pointer_register : trivial_register<tags::ip> {};

NGS_LIB_MODULE_END