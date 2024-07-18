#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct window
{
	NGS_PP_INJECT_BEGIN(window);
public:
	using handle_type = ::GLFWwindow*;

	friend struct basic_glfw_guard;

private:
	window(::std::string_view title, ::std::size_t width, ::std::size_t height)
		: _handle(::glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.data(), nullptr, nullptr))
	{
		if(!_handle)
		{
			throw std::runtime_error("failed to create window");
		}
		// unmovable
		::glfwSetWindowUserPointer(_handle, this);

		active();
	}
public:
	~window()
	{
		::glfwDestroyWindow(_handle);
	}

	window(const self_type&) = delete;
	self_type& operator=(const self_type&) = delete;

	[[nodiscard]] decltype(auto) should_close() const noexcept { return ::glfwWindowShouldClose(_handle); }
	decltype(auto) close() const noexcept { ::glfwSetWindowShouldClose(_handle, GLFW_TRUE); }

#if (GLFW_VERSION_MAJOR >= 3) && (GLFW_VERSION_MINOR >= 4)
	[[nodiscard]] decltype(auto) title() const noexcept { return ::std::string_view(::glfwGetWindowTitle(_handle)); }
#endif
	decltype(auto) reset_title(::std::string_view title) const { ::glfwSetWindowTitle(_handle, title.data()); }

	decltype(auto) move_to(int x, int y) const { ::glfwSetWindowPos(_handle, x, y); }
	[[nodiscard]] decltype(auto) position() const
	{
		int x, y;
		::glfwGetWindowPos(_handle, &x, &y);
		return ::std::make_pair(x, y);
	}

	decltype(auto) resize(int width, int height) const { ::glfwSetWindowSize(_handle, width, height); }
	[[nodiscard]] decltype(auto) size() const noexcept
	{
		int width, height;
		::glfwGetWindowSize(_handle, &width, &height);
		return ::std::make_pair(width, height);
	}
	[[nodiscard]] decltype(auto) size_limit(int min_width, int min_height, int max_width, int max_height) const noexcept
	{
		::glfwSetWindowSizeLimits(_handle, min_width, min_height, max_width, max_height);
	}
	[[nodiscard]] decltype(auto) aspect_ratio(int numerator, int denominator) const noexcept { ::glfwSetWindowAspectRatio(_handle, numerator, denominator); }

	[[nodiscard]] decltype(auto) framebuffer_size() const noexcept
	{
		int width, height;
		::glfwGetFramebufferSize(_handle, &width, &height);
		return ::std::make_pair(width, height);
	}

	[[nodiscard]] decltype(auto) frame_size() const noexcept
	{
		int left, top, right, bottom;
		::glfwGetWindowFrameSize(_handle, &left, &top, &right, &bottom);
		return ::std::make_tuple(left, top, right, bottom);
	}

	decltype(auto) maximize() const noexcept { ::glfwMaximizeWindow(_handle); }
	decltype(auto) minimize() const noexcept { ::glfwIconifyWindow(_handle); }
	decltype(auto) restore() const noexcept { ::glfwRestoreWindow(_handle); }
	decltype(auto) focus() const noexcept { ::glfwFocusWindow(_handle); }
	decltype(auto) hide() const noexcept { ::glfwHideWindow(_handle); }
	decltype(auto) show() const noexcept { ::glfwShowWindow(_handle); }

	decltype(auto) active() const noexcept { ::glfwMakeContextCurrent(_handle); }

	decltype(auto) swap_buffer() const noexcept { ::glfwSwapBuffers(_handle); }

	[[nodiscard]] decltype(auto) key_state(int key) const noexcept { return ::glfwGetKey(_handle, key); }
	[[nodiscard]] decltype(auto) mouse_state(int button) const noexcept { return ::glfwGetMouseButton(_handle, button); }

	[[nodiscard]] decltype(auto) get_monitor() const noexcept { return ::glfwGetWindowMonitor(_handle); }
	[[nodiscard]] decltype(auto) get_video_mode() const noexcept { return ::glfwGetVideoMode(get_monitor()); }



	[[nodiscard]] decltype(auto) get_context() const noexcept { return _handle; }
	[[nodiscard]] static auto&& get_self(handle_type context) noexcept { return *reinterpret_cast<self_type*>(::glfwGetWindowUserPointer(context)); }

	handle_type _handle{};

#define NGL_WINDOW_CALLBACK_DEFINE(function_name,function_name_lower,...)										\
private:																										\
	using _glfw_##function_name_lower##_callback_t = void(self_type&, __VA_ARGS__);								\
	::std::function<_glfw_##function_name_lower##_callback_t> _##function_name_lower##_callback = nullptr;		\
	static void _glfw_##function_name_lower##_callback_wrapper(handle_type context, auto... args) {				\
		auto&& window = self_type::get_self(context);															\
		window._##function_name_lower##_callback(window, args...);												\
	}																											\
public:																											\
	void set_##function_name_lower##_callback(const ::std::function<_glfw_##function_name_lower##_callback_t>& callback){ \
		_##function_name_lower##_callback = callback;															\
		::glfwSet##function_name##Callback(_handle,_glfw_##function_name_lower##_callback_wrapper<__VA_ARGS__>);\
	}																											\
//
	NGL_WINDOW_CALLBACK_DEFINE(WindowPos, position, int, int);				//void GLFWwindowposfun(GLFWwindow* window, int xpos, int ypos)
	NGL_WINDOW_CALLBACK_DEFINE(WindowSize, size, int, int);					//void GLFWwindowsizefun(GLFWwindow* window, int width, int height)
	NGL_WINDOW_CALLBACK_DEFINE(WindowFocus, focus, int);					//void GLFWwindowfocusfun(GLFWwindow* window, int focused)
	NGL_WINDOW_CALLBACK_DEFINE(WindowIconify, iconify, int);				//void GLFWwindowiconifyfun(GLFWwindow* window, int iconified)
	NGL_WINDOW_CALLBACK_DEFINE(FramebufferSize, framebuffer_size, int, int);//void GLFWframebuffersizefun(GLFWwindow* window, int width, int height)
	NGL_WINDOW_CALLBACK_DEFINE(Key, key, int, int, int, int);				//void GLFWkeyfun(GLFWwindow* window, int key, int scancode, int action, int mods)
	NGL_WINDOW_CALLBACK_DEFINE(MouseButton, mouse_button, int, int, int);	//void GLFWcharfun(GLFWwindow* window, unsigned int codepoint)
	NGL_WINDOW_CALLBACK_DEFINE(CursorPos, cursor_position, double, double);	//void GLFWcursorposfun(GLFWwindow* window, double xpos, double ypos)
	NGL_WINDOW_CALLBACK_DEFINE(CursorEnter, cursor_enter, int);				//void GLFWcursorenterfun(GLFWwindow* window, int entered)
	NGL_WINDOW_CALLBACK_DEFINE(Scroll, scroll, double, double);				//void GLFWscrollfun(GLFWwindow* window, double xoffset, double yoffset)
	NGL_WINDOW_CALLBACK_DEFINE(Drop, drop, int, const char**);				//void GLFWdropfun(GLFWwindow* window, int count, const char** paths)
};

NGS_LIB_MODULE_END