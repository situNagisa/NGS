#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//si
struct source_index_register : extend_trivial_register<bit16::source_index_register, tags::esi> {};
//di
struct destination_index_register : extend_trivial_register<bit16::destination_index_register, tags::edi> {};

NGS_LIB_MODULE_END