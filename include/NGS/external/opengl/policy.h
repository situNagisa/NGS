#pragma once

#include "./policy/glsl.h"
#include "./policy/shader.h"
#include "./policy/buffer.h"
#include "./policy/indices.h"
#include "./policy/vertex.h"
#include "./policy/layout.h"
#include "./policy/image.h"
#include "./policy/texture.h"
#include "./policy/renderbuffer.h"
#include "./policy/framebuffer.h"

NGS_LIB_MODULE_EXPORT(shader);
NGS_LIB_MODULE_EXPORT(indices_buffer);
NGS_LIB_MODULE_EXPORT(vertex_buffer);
NGS_LIB_MODULE_EXPORT(layout);

NGS_LIB_MODULE_EXPORT(image);
NGS_LIB_MODULE_EXPORT(make_image);
NGS_LIB_MODULE_EXPORT(texture_1d);
NGS_LIB_MODULE_EXPORT(texture_1d_array);
NGS_LIB_MODULE_EXPORT(texture_2d);
NGS_LIB_MODULE_EXPORT(texture_2d_array);
NGS_LIB_MODULE_EXPORT(texture_3d);
NGS_LIB_MODULE_EXPORT(texture_rectangle);

NGS_LIB_MODULE_EXPORT(renderbuffer);

NGS_LIB_MODULE_EXPORT(framebuffer);
NGS_LIB_MODULE_EXPORT(read_framebuffer);
NGS_LIB_MODULE_EXPORT(draw_framebuffer);

#include "NGS/lib/module_end.h"