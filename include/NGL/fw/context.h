#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"

NGL_BEGIN

using GLFW_Context = GLFWwindow*;
static_assert(Context<GLFW_Context>, "GLFW_Context must satisfy Context concept");


class GLFW_ContextManager {
public:
	static GLFW_Context GetContext();
	static void SetContext(GLFW_Context window);
private:
};
static_assert(ContextManager<GLFW_ContextManager, GLFW_Context>, "GLFW_ContextManager must satisfy ContextManager concept");


NGL_END
