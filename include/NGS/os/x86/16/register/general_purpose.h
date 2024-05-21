#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ax
struct accumulator_register : trivial_register<registers::ax> {};
//bx
struct base_register : trivial_register<registers::bx> {};
//cx
struct counter_register : trivial_register<registers::cx> {};
//dx
struct data_register : trivial_register<registers::dx> {};

NGS_LIB_MODULE_END