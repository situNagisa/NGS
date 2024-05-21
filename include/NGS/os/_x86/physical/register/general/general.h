#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using accumulator_register = ::std::uint32_t; //ax
using base_register = ::std::uint32_t; //bx
using count_register = ::std::uint32_t; //cx
using data_register = ::std::uint32_t;	// dx
using source_index_register = ::std::uint32_t; //si
using destination_index_register = ::std::uint32_t; //di
using base_pointer_register = ::std::uint32_t; // bp
using stack_pointer_register = ::std::uint32_t; // sp

NGS_LIB_MODULE_END