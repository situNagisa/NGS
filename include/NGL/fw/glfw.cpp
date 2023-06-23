#include "NGL/fw/glfw.h"
#include "NGL/fw/window.h"

NGL_BEGIN

NGS_HPP_INLINE GLFW::GLFW(int major, int minor) {
	if (!glfwInit())
		NGS_ASSERT(false, "glfw init fail!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if NGS_PLATFORM == NGS_MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

NGS_HPP_INLINE GLFW::~GLFW()
{
	glfwTerminate();
}

void GLFW::_SET_CURRENT_CONTEXT(context_type::handle_type window)
{
	glfwMakeContextCurrent(window);
}

NGS_HPP_INLINE void GLFW::PollEvents() { glfwPollEvents(); }

NGL_END


