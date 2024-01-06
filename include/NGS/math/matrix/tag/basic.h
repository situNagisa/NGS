#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//struct matrix : vectors::tags::vector {};
using matrix = vectors::tags::vector;

using vectors::tags::retag;
using vectors::tags::trait_t;
using vectors::tags::tag;

NGS_LIB_MODULE_END