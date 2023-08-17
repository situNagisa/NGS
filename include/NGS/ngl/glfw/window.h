#pragma once

#include "NGS/ngl/glfw/defined.h"
#include "NGS/ngl/glfw/cursor.h"
#include "NGS/ngl/config.h"
#include "NGS/ngl/base/target.h"

NGL_FW_BEGIN

class NGS_API  Window : public DeleteCopy {
public:
	using context_t = GLFWwindow*;
public:
	Window(std::string_view title, const Point2i& size)
		: _title(title)
	{
		_context = glfwCreateWindow(size.x, size.y, _title.c_str(), nullptr, nullptr);
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

	void SetTitle(std::string_view title) {
		_title = title;
		glfwSetWindowTitle(_context, _title.c_str());
	}
	//void SetIcon(const std::vector<GLFWimage>& icons);
	void SetPosition(int x, int y) { glfwSetWindowPos(_context, x, y); }
	void SetPosition(const Point2i& pos) { SetPosition(pos.x, pos.y); }
	void SetSize(int width, int height) { glfwSetWindowSize(_context, width, height); }
	void SetSize(const Point2i& size) { SetSize(size.x, size.y); }
	void SetInputMode(int mode, int value) { glfwSetInputMode(_context, mode, value); }
	void SetCursor(Cursor* cursor) { glfwSetCursor(_context, cursor->GetContext()); }
	void SetCursorPosition(double x,double y){ glfwSetCursorPos(_context, x, y); }
	void SetCursorPosition(const Point2d& pos) { SetCursorPosition(pos.x, pos.y); }

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
	Point2d GetCursorPosition()const {
		double x, y;
		glfwGetCursorPos(_context, &x, &y);
		return { x,y };
	}
	const std::string& GetTitle()const { return _title; }

	void Active();
	void Iconify() { glfwIconifyWindow(_context); }
	void Restore() { glfwRestoreWindow(_context); }
	void Maximize() { glfwMaximizeWindow(_context); }
	void Show() { glfwShowWindow(_context); }
	void Hide() { glfwHideWindow(_context); }
	void Focus() { glfwFocusWindow(_context); }

	void SwapBuffer()const { glfwSwapBuffers(_context); }

	int GetKeyState(int key)const { return glfwGetKey(_context, key); }
	bool IsKeyDown(int key)const { return GetKeyState(key) == GLFW_PRESS; }
	bool IsKeyRepeat(int key)const { return GetKeyState(key) == GLFW_REPEAT; }
	bool IsKeyRelease(int key)const { return GetKeyState(key) == GLFW_RELEASE; }

	int GetMouseState(int button)const { return glfwGetMouseButton(_context, button); }
	bool IsMouseDown(int button)const { return GetMouseState(button) == GLFW_PRESS; }
	bool IsMouseRelease(int button)const { return GetMouseState(button) == GLFW_RELEASE; }

	context_t GetContext()const { return _context; }

#define NGL_WINDOW_CALLBACK_DEFINE(function_name,function_name_lower,...)	\
public:\
	using glfw_##function_name_lower##_callback_t = void(Window*, __VA_ARGS__);\
private:\
	std::function<glfw_##function_name_lower##_callback_t> _##function_name_lower##_callback = nullptr;\
	template<class ... T>\
	static void _glfw_##function_name_lower##_callback_wrapper(context_t context, T... args) {\
		auto it = _handle_map.find(context);\
		NGS_ASSERT(it != _handle_map.end());\
		Window* window = it->second;\
		window->_##function_name_lower##_callback(window, std::forward<T>(args)...);\
	}\
public:\
	void Set##function_name##Callback(const std::function<glfw_##function_name_lower##_callback_t>& callback){ \
		glfwSet##function_name##Callback(_context,_glfw_##function_name_lower##_callback_wrapper<__VA_ARGS__>);\
		_##function_name_lower##_callback = callback;\
	}\
//
	NGL_WINDOW_CALLBACK_DEFINE(WindowPos, position, int, int);
	NGL_WINDOW_CALLBACK_DEFINE(WindowSize, size, int, int);
	NGL_WINDOW_CALLBACK_DEFINE(WindowClose, close);
	NGL_WINDOW_CALLBACK_DEFINE(WindowRefresh, refresh);
	NGL_WINDOW_CALLBACK_DEFINE(WindowFocus, focus, int);
	NGL_WINDOW_CALLBACK_DEFINE(WindowIconify, iconify, int);
	NGL_WINDOW_CALLBACK_DEFINE(FramebufferSize, framebuffer_size, int, int);
	NGL_WINDOW_CALLBACK_DEFINE(Key, key, int, int, int, int);
	NGL_WINDOW_CALLBACK_DEFINE(MouseButton, mouse_button, int, int, int);
	NGL_WINDOW_CALLBACK_DEFINE(CursorPos, cursor_position, double, double);
	//NGL_WINDOW_CALLBACK_DEFINE(CursorPosition, cursor_position, double, double);
	NGL_WINDOW_CALLBACK_DEFINE(CursorEnter, cursor_enter, int);
	NGL_WINDOW_CALLBACK_DEFINE(Scroll, scroll, double, double);
	NGL_WINDOW_CALLBACK_DEFINE(Drop, drop, int, const char**);
	//NGL_WINDOW_CALLBACK_DEFINE(Joystick, joystick, int, int);
	//NGL_WINDOW_CALLBACK_DEFINE(Monitor, monitor, int);
#undef NGL_WINDOW_CALLBACK_DEFINE


private:
	context_t _context = nullptr;
	std::string _title = "NGL Window";
private:
	inline static std::unordered_map<context_t, Window*> _handle_map = {};
};

NGL_FW_END
