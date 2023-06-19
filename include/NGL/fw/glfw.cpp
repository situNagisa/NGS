#include "NGL/fw/glfw.h"
#include "NGL/fw/window.h"

NGL_BEGIN

NGS_HPP_INLINE GLFW::GLFW(int major, int minor) {
	if (!glfwInit())
		NGS_Assert(false, "glfw init fail!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if NGS_PLATFORM == NGS_MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

NGS_HPP_INLINE GLFW::~GLFW()
{
	while (_windows.size()) {
		auto& [gl_window, window] = *_windows.begin();
		DestroyWindow(window);
	}
	glfwTerminate();
}

NGS_HPP_INLINE GLFW::__window_ptr GLFW::CreateWindow()
{
	auto window = NGS_NEW(new Window());
	_windows[window->GetContext()] = window;
	return window;
}

NGS_HPP_INLINE void GLFW::DestroyWindow(__window_ptr window)
{
	_windows.erase(window->GetContext());
	window->Close();
	NGS_DELETE(window);
}

NGS_HPP_INLINE bool GLFW::ShouldClose() const
{
	for (auto pair : _windows) {
		auto& window = *pair.second;
		if (window.ShouldClose())return true;
	}
	return false;
}

NGS_HPP_INLINE void GLFW::PollEvents() { glfwPollEvents(); }

NGL_END


