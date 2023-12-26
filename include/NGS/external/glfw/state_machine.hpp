#pragma once

#include "./glfw.h"

NGS_LIB_BEGIN

NGS_HPP_INLINE void GLFW::init_opengl(int major, int minor)
{
	if (!glfwInit())
		NGS_ASSERT(false, "glfw init fail!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(NGS_SYSTEM_IS_MAC)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

NGS_HPP_INLINE void GLFW::init_vulkan()
{
	if (!glfwInit())
		NGS_ASSERT(false, "glfw init fail!");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

NGS_HPP_INLINE void GLFW::destroy()
{
	terminate();
}

NGS_HPP_INLINE void GLFW::select(state_type* window)
{
	_current = window;
	glfwMakeContextCurrent(window->get_context());
	//static bool success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	//NGS_ASSERT(success);
}

NGS_HPP_INLINE void GLFW::poll_events()
{
	glfwPollEvents();
}

NGS_HPP_INLINE void GLFW::terminate()
{
	glfwTerminate();
}


NGS_LIB_END
