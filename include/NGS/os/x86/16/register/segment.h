#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//cs
struct code_segment_register : trivial_register<registers::cs> {};
//ds
struct data_segment_register : trivial_register<registers::ds> {};
//es
struct extra_segment_register : trivial_register<registers::es> {};
//fs
struct more_extra_segment_register : trivial_register<registers::fs> {};
//gs
struct yet_more_extra_segment_register : trivial_register<registers::gs> {};
//ss
struct stack_segment_register : trivial_register<registers::ss> {};

NGS_LIB_MODULE_END