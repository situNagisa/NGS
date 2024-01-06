#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct trivial : vector {};
struct zero : trivial {};

NGS_LIB_MODULE_END