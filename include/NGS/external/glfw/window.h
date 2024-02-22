#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

class NGS_DLL_API window : public bases::delete_copy {
protected:
	using self_type = window;
public:
	using context_t = GLFWwindow*;
public:
	window(std::string_view title, const math::vectors::vector2i& size);
	window() : self_type("", { 1,1 }) {};
	window(std::string_view title, int width, int height) : self_type(title, { width,height }) {}
	~window()noexcept;


	window(self_type&& other) noexcept
	{
		_context = other._context;
		other._context = nullptr;
		_handle_map[_context] = this;
	}
	self_type& operator=(self_type&& other) noexcept
	{
		_context = other._context;
		other._context = nullptr;
		_handle_map[_context] = this;
		return *this;
	}

	void close();
	bool is_should_close()const noexcept;
	void should_close()const noexcept;

	void set_title(std::string_view title);
	auto&& get_title()const { return _title; }


	//void SetIcon(const std::vector<GLFWimage>& icons);
	void set_position(int x, int y);
	void set_position(const math::vectors::vector2i& pos) { set_position(pos[0], pos[1]); }
	math::vectors::vector2i get_position()const;

	void    set_size(int width, int height);
	void    set_size(const math::vectors::vector2i& size) { set_size(size[0], size[1]); }
	math::vectors::vector2i get_size()const;

	void set_input_mode(int mode, int value);
	void    set_cursor(GLFWcursor* cursor);
	void    set_cursor_position(double x, double y);
	void    set_cursor_position(const math::vectors::vector2d& pos) { set_cursor_position(pos[0], pos[1]); }
	math::vectors::vector2d get_cursor_position()const;

	GLFWmonitor* get_monitor()const;

	math::vectors::vector2i						get_framebuffer_size() const;

	std::pair<math::vectors::vector2i, math::vectors::vector2i> get_frame_size()const;

	//Rectanglei                  get_client_bound()const;

	void active();
	void iconify();
	void restore();
	void maximize();
	void show();
	void hide();
	void focus();

	void swap_buffer()const;

	int  get_key_state(int key)const;
	bool is_key_down(int key)const { return get_key_state(key) == GLFW_PRESS; }
	bool is_key_repeat(int key)const { return get_key_state(key) == GLFW_REPEAT; }
	bool is_key_release(int key)const { return get_key_state(key) == GLFW_RELEASE; }

	int  get_mouse_state(int button)const;
	bool is_mouse_down(int button)const { return get_mouse_state(button) == GLFW_PRESS; }
	bool is_mouse_release(int button)const { return get_mouse_state(button) == GLFW_RELEASE; }

	auto&& get_context()const { return _context; }

#define NGL_WINDOW_CALLBACK_DEFINE(function_name,function_name_lower,...)										\
public:																											\
	using glfw_##function_name_lower##_callback_t = void(self_type*, __VA_ARGS__);								\
private:																										\
	std::function<glfw_##function_name_lower##_callback_t> _##function_name_lower##_callback = nullptr;			\
	template<class ... T>																						\
	static void _glfw_##function_name_lower##_callback_wrapper(context_t context, T... args) {					\
		auto it = _handle_map.find(context);																	\
		NGS_ASSERT(it != _handle_map.end());																	\
		self_type* window = it->second;																			\
		window->_##function_name_lower##_callback(window, std::forward<T>(args)...);							\
	}																											\
public:																											\
	void set_##function_name_lower##_callback(const std::function<glfw_##function_name_lower##_callback_t>& callback){ \
		glfwSet##function_name##Callback(_context,_glfw_##function_name_lower##_callback_wrapper<__VA_ARGS__>);	\
		_##function_name_lower##_callback = callback;															\
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
#undef NGL_WINDOW_CALLBACK_DEFINE

#if defined(VK_VERSION_1_0)
	VkSurfaceKHR create_surface(VkInstance instance, VkAllocationCallbacks* allocator = nullptr)const;
#endif

private:
	context_t _context = nullptr;
	std::string _title = "nagisa::external::glfw";
private:
	inline static std::unordered_map<context_t, self_type*> _handle_map = {};
};

NGS_LIB_END