#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline decltype(auto) load_opengl()
{
	return ::gladLoadGL();
}

inline decltype(auto) load(::GLADloadproc loader)
{
	return ::gladLoadGLLoader(loader);
}

inline decltype(auto) load(void* loader)
{
	return NGS_LIB_MODULE_NAME::load(reinterpret_cast<GLADloadproc>(loader));
}

NGS_LIB_MODULE_END