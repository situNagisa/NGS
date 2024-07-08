#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//cs
struct code_segment_register : trivial_register<tags::cs> {};
//ds
struct data_segment_register : trivial_register<tags::ds> {};
//es
struct extra_segment_register : trivial_register<tags::es> {};
//fs
struct more_extra_segment_register : trivial_register<tags::fs> {};
//gs
struct yet_more_extra_segment_register : trivial_register<tags::gs> {};
//ss
struct stack_segment_register : trivial_register<tags::ss> {};

NGS_LIB_MODULE_END