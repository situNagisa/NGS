#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/config.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/base/target.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class Window : public DeleteCopy {
public:
	using context_t = GLFWwindow*;
public:
	Window(std::string_view title, const Point2i& size) {
		_context = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
		NGS_ASSERT(_context);
		_handle_map.insert({ _context, this });

		Active();
	}
	Window() : Window("", { 1,1 }) {};
	Window(std::string_view title, int width, int height) : Window(title, { width,height }) {}
	~Window()noexcept {
		_handle_map.erase(_context);

		glfwDestroyWindow(_context);
		_context = nullptr;
	}
	Window(Window&& other) {
		_context = other._context;
		other._context = nullptr;
		_handle_map[_context] = this;
	}

	void Close() { glfwSetWindowShouldClose(_context, true); }
	bool IsShouldClose()const noexcept { return glfwWindowShouldClose(_context); }
	void ShouldClose()const noexcept { glfwSetWindowShouldClose(_context, GL_TRUE); }

	void SetTitle(std::string_view title) { glfwSetWindowTitle(_context, title.data()); }
	//void SetIcon(const std::vector<GLFWimage>& icons);
	void SetPosition(int x, int y) { glfwSetWindowPos(_context, x, y); }
	void SetPosition(const Point2i& pos) { SetPosition(pos.x, pos.y); }
	void SetSize(int width, int height) { glfwSetWindowSize(_context, width, height); }
	void SetSize(const Point2i& size) { SetSize(size.x, size.y); }
	void SetInputMode(int mode, int value) { glfwSetInputMode(_context, mode, value); }

	GLFWmonitor* GetMonitor()const;
	Point2i GetPosition()const {
		int x, y;
		glfwGetWindowPos(_context, &x, &y);
		return { x,y };
	}
	Point2i GetSize()const {
		int width, height;
		glfwGetWindowSize(_context, &width, &height);
		return { width,height };
	}
	Point2i GetFramebufferSize() const {
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(_context, &bufferWidth, &bufferHeight);
		return { bufferWidth,bufferHeight };
	}
	Rectanglei GetFrameBounds()const {
		int left, top, right, bottom;
		glfwGetWindowFrameSize(_context, &left, &top, &right, &bottom);
		return { left,top,right - left,bottom - top };
	}
	Rectanglei GetClientBounds()const {
		auto pos = GetPosition();
		auto size = GetSize();
		return { pos,size };
	}

	void Active();
	void Iconify() { glfwIconifyWindow(_context); }
	void Restore() { glfwRestoreWindow(_context); }
	void Maximize() { glfwMaximizeWindow(_context); }
	void Show() { glfwShowWindow(_context); }
	void Hide() { glfwHideWindow(_context); }
	void Focus() { glfwFocusWindow(_context); }

	void SwapBuffer()const { glfwSwapBuffers(_context); }

	context_t GetContext()const { return _context; }
private:
	context_t _context = nullptr;
private:
	inline static std::unordered_map<context_t, Window*> _handle_map = {};
};
NGS_END
NGL_TARGET_BEGIN
class GLFW : public Target<GLFW, objects::Window>, public Singleton<GLFW> {
public:
	NGS_TYPE_DEFINE(objects::Window, window);

private:
	friend class Target<GLFW, objects::Window>;
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

NGL_OBJ_BEGIN
inline void Window::Active() { targets::GLFW::I().Select(this); }
NGS_END

NGL_END
