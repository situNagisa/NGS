#pragma once

#include "NGS/ngl/glfw/defined.h"
#include "NGS/ngl/config.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/glfw/window.h"

NGL_BEGIN
NGL_TARGET_BEGIN
class GLFW : public Target<GLFW, fw::Window>, public Singleton<GLFW> {
public:
	NGS_TYPE_DEFINE(fw::Window, window);

private:
	friend class Target<GLFW, fw::Window>;
	friend class Singleton<GLFW>;
	GLFW(int major = NGL_OPENGL_MAJOR, int minor = NGL_OPENGL_MINOR) {
		if (!glfwInit())
			NGS_ASSERT(false, "glfw init fail!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if NGS_PLATFORM == NGS_MAC
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}
	static void _Select(state_type* window) {
		glfwMakeContextCurrent(window->GetContext());
		static bool success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NGS_ASSERT(success);
	}
public:
	~GLFW() { glfwTerminate(); }

	void PollEvents() { glfwPollEvents(); }
	void Terminate() { glfwTerminate(); }
};
NGS_END
NGL_END

NGL_FW_BEGIN
inline void Window::Active() { targets::GLFW::I().Select(this); }
NGL_FW_END