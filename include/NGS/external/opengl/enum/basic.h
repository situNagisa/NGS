#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class fundamental : gl_enum_t
{
    floating = GL_FLOAT,
    double_floating = GL_DOUBLE,
    integral = GL_INT,
    unsigned_integral = GL_UNSIGNED_INT,
    short_integral = GL_SHORT,
    unsigned_short = GL_UNSIGNED_SHORT,
    byte = GL_BYTE,
    unsigned_byte = GL_UNSIGNED_BYTE,
    half_float = GL_HALF_FLOAT,
};

enum class format : gl_enum_t
{
	red = GL_RED,
	green = GL_GREEN,
	blue = GL_BLUE,
	alpha = GL_ALPHA,
	rg = GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,
	bgr = GL_BGR,
	bgra = GL_BGRA,
	depth = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil = GL_STENCIL_INDEX,
};

enum class internal_format : gl_enum_t
{
	red = GL_RED,
	rg = GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,
	depth = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil = GL_STENCIL_INDEX,
};



NGS_LIB_MODULE_END