#pragma once

#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::descriptor;

using NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t;

using NGS_EXTERNAL_OPENGL_BUFFER_NS::indices_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_array_indices_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_indices_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_vector_indices_buffer;

using NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_array_vertex_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_buffer;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_vector_vertex_buffer;

using NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_array_vertex_group;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_group;
using NGS_EXTERNAL_OPENGL_BUFFER_NS::make_vector_vertex_group;

NGS_LIB_MODULE_END