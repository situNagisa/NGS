#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/gl.h"

NGL_BEGIN

class Shader {
public:

public:
	Shader(void_ptr_cst vertext, void_ptr_cst fragment);
	Shader(void_ptr_cst vertext, void_ptr_cst fragment, void_ptr_cst geometry);
	~Shader();
};

NGL_END
