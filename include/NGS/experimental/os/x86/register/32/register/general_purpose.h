#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ax
struct accumulator_register : extend_trivial_register<bit16::accumulator_register, tags::eax> {};
//bx
struct base_register : extend_trivial_register<bit16::base_register, tags::ebx> {};
//cx
struct counter_register : extend_trivial_register<bit16::counter_register, tags::ecx> {};
//dx
struct data_register : extend_trivial_register<bit16::data_register, tags::edx> {};

NGS_LIB_MODULE_END