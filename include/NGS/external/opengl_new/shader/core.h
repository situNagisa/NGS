#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::code_char_t;

using details::shader_code;
using details::code;
using details::vertex_code;
using details::fragment_code;
using details::geometry_code;
using details::compute_code;
using details::tess_control_code;
using details::tess_evaluation_code;
using details::make_compiled_code;

using details::uniform_memory;

using details::pair;
using details::context;
using details::shader_uniform;
using details::shader;

NGS_LIB_END