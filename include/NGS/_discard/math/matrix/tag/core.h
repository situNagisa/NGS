#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct triangle : matrix {};

struct upper_triangle : triangle {};
struct lower_triangle : triangle {};

struct diagonal : matrix {};
struct identity : diagonal {};

struct trivial : matrix {};
struct zero : trivial {};

NGS_LIB_MODULE_END