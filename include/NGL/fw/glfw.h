#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/config.h"
#include "NGL/fw/context.h"

NGL_BEGIN

class Window;

class GLFW : public Singleton<GLFW> {
public:
	NGS_TYPE_DEFINE(Window, window);

private:
	friend class Singleton<GLFW>;
	GLFW(int major = NGL_OPENGL_MAJOR, int minor = NGL_OPENGL_MINOR);
	~GLFW();
public:

#undef CreateWindow
	__window_ptr CreateWindow();
	void DestroyWindow(__window_ptr window);
	__window_ptr GetCurrentWindow() { return _windows.at(GLFW_ContextManager::GetContext()); }
	__window_ptr_cst GetCurrentWindow()const { return _windows.at(GLFW_ContextManager::GetContext()); }

	bool ShouldClose()const;

	void PollEvents();
private:

private:
	std::unordered_map<GLFW_Context, __window_ptr> _windows = {};
};

NGL_END
