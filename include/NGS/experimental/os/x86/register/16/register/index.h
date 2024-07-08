#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//si
struct source_index_register : trivial_register<tags::si> {};
//di
struct destination_index_register : trivial_register<tags::di> {};

NGS_LIB_MODULE_END