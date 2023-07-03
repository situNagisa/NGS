#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/config.h"
#include "NGL/context.h"

NGL_BEGIN

class Window : public Context<GLFWwindow*> {
public:

public:
	Window(std::string_view title, const Point2i& size) {
		_handle = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
		NGS_ASSERT(_handle);
		_handle_map.insert({ _handle, this });

		Active();
	}
	Window() : Window("", { 1,1 }) {};
	Window(std::string_view title, int width, int height) : Window(title, { width,height }) {}
	~Window()noexcept {
		_handle_map.erase(_handle);

		glfwDestroyWindow(_handle);
		_handle = nullptr;
	}

	void Close() { glfwSetWindowShouldClose(_handle, true); }
	bool ShouldClose()const noexcept { return glfwWindowShouldClose(_handle); }

	void SetTitle(std::string_view title) { glfwSetWindowTitle(_handle, title.data()); }
	//void SetIcon(const std::vector<GLFWimage>& icons);
	void SetPosition(int x, int y) { glfwSetWindowPos(_handle, x, y); }
	void SetPosition(const Point2i& pos) { SetPosition(pos.x, pos.y); }
	void SetSize(int width, int height) { glfwSetWindowSize(_handle, width, height); }
	void SetSize(const Point2i& size) { SetSize(size.x, size.y); }
	void SetInputMode(int mode, int value) { glfwSetInputMode(_handle, mode, value); }

	GLFWmonitor* GetMonitor()const;
	Point2i GetPosition()const {
		int x, y;
		glfwGetWindowPos(_handle, &x, &y);
		return { x,y };
	}
	Point2i GetSize()const {
		int width, height;
		glfwGetWindowSize(_handle, &width, &height);
		return { width,height };
	}
	Rectanglei GetFrameSize()const {
		int left, top, right, bottom;
		glfwGetWindowFrameSize(_handle, &left, &top, &right, &bottom);
		return { left,top,right - left,bottom - top };
	}

	void Active();
	void Iconify() { glfwIconifyWindow(_handle); }
	void Restore() { glfwRestoreWindow(_handle); }
	void Maximize() { glfwMaximizeWindow(_handle); }
	void Show() { glfwShowWindow(_handle); }
	void Hide() { glfwHideWindow(_handle); }
	void Focus() { glfwFocusWindow(_handle); }

	void SwapBuffer()const { glfwSwapBuffers(_handle); }
private:

private:
	inline static std::unordered_map<handle_type, Window*> _handle_map = {};
};

class GLFW : public Current<Window, GLFW> {
public:
	NGS_TYPE_DEFINE(Window, window);

private:
	friend class base;
	friend class Constructor;
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
	static void _SET_CURRENT_CONTEXT(context_type::handle_type window) {
		glfwMakeContextCurrent(window);
		static bool success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NGS_ASSERT(success);
	}
public:
	~GLFW() { glfwTerminate(); }

	void PollEvents() { glfwPollEvents(); }
};
inline static auto glfw = Constructor::Construct<GLFW>();

void Window::Active() { glfw.SetContext(this); }

NGL_END
