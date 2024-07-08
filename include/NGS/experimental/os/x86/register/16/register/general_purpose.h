#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ax
struct accumulator_register : trivial_register<tags::ax> {};
//bx
struct base_register : trivial_register<tags::bx> {};
//cx
struct counter_register : trivial_register<tags::cx> {};
//dx
struct data_register : trivial_register<tags::dx> {};

NGS_LIB_MODULE_END