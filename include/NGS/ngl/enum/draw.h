#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

enum class  ElementDrawMode : GLenum {
	points = GL_POINTS,

	lines = GL_LINES,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,

	triangles = GL_TRIANGLES,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,

	patches = GL_PATCHES,
};
enum class  DrawMode : GLenum {
	points = GL_POINTS,

	lines = GL_LINES,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,

	line_strip_adjacency = GL_LINE_STRIP_ADJACENCY,
	lines_adjacency = GL_LINES_ADJACENCY,

	triangles = GL_TRIANGLES,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,

	triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	triangles_adjacency = GL_TRIANGLES_ADJACENCY,
};

NGL_END
