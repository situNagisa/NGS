#pragma once

#include "./state_machine.h"
#include "./window.h"

NGS_LIB_BEGIN

NGS_HPP_INLINE window::window(::std::string_view title, int width, int height)
	: _title(title)
{
	_context = ::glfwCreateWindow(width, height, _title.c_str(), nullptr, nullptr);
	NGS_ASSERT(_context);
	_handle_map.insert({ _context, this });

	active();
}

NGS_HPP_INLINE window::~window() noexcept
{
	_handle_map.erase(_context);

	glfwDestroyWindow(_context);
	_context = nullptr;
}

NGS_HPP_INLINE void window::close() { ::glfwSetWindowShouldClose(_context, true); }

NGS_HPP_INLINE bool window::is_should_close() const noexcept { return ::glfwWindowShouldClose(_context); }

NGS_HPP_INLINE void window::should_close() const noexcept { ::glfwSetWindowShouldClose(_context, GL_TRUE); }

NGS_HPP_INLINE void window::set_title(std::string_view title) {
	_title = title;
	::glfwSetWindowTitle(_context, _title.c_str());
}

NGS_HPP_INLINE void window::set_position(int x, int y) { ::glfwSetWindowPos(_context, x, y); }

NGS_HPP_INLINE ::std::pair<int,int> window::get_position() const
{
	int x, y;
	::glfwGetWindowPos(_context, &x, &y);
	return { x,y };
}

NGS_HPP_INLINE void window::set_size(int width, int height) { ::glfwSetWindowSize(_context, width, height); }

NGS_HPP_INLINE::std::pair<int, int> window::get_size() const
{
	int width, height;
	::glfwGetWindowSize(_context, &width, &height);
	return { width,height };
}

NGS_HPP_INLINE void window::set_input_mode(int mode, int value) { ::glfwSetInputMode(_context, mode, value); }

NGS_HPP_INLINE void window::set_cursor(GLFWcursor* cursor)
{
	::glfwSetCursor(_context, cursor);
}

NGS_HPP_INLINE void window::set_cursor_position(double x, double y)
{
	::glfwSetCursorPos(_context, x, y);
}

NGS_HPP_INLINE ::std::pair<double,double> window::get_cursor_position() const
{
	double x, y;
	::glfwGetCursorPos(_context, &x, &y);
	return { x,y };
}

NGS_HPP_INLINE::std::pair<int, int> window::get_framebuffer_size() const
{
	int buffer_width;
	int buffer_height;
	::glfwGetFramebufferSize(_context, &buffer_width, &buffer_height);
	return { buffer_width,buffer_height };
}

NGS_HPP_INLINE ::std::tuple<int,int,int,int> window::get_frame_size() const
{
	int left, top, right, bottom;
	::glfwGetWindowFrameSize(_context, &left, &top, &right, &bottom);
	return { left, top, right, bottom };
}

//NGS_HPP_INLINE Rectanglei window::get_client_bound() const
//{
//	auto pos = get_position();
//	auto size = get_size();
//	return { pos,size };
//}

NGS_HPP_INLINE void window::active()
{
	GLFW::instance().select(this);
}

NGS_HPP_INLINE void window::iconify()
{
	::glfwIconifyWindow(_context);
}

NGS_HPP_INLINE void window::restore()
{
	::glfwRestoreWindow(_context);
}

NGS_HPP_INLINE void window::maximize()
{
	::glfwMaximizeWindow(_context);
}

NGS_HPP_INLINE void window::show()
{
	::glfwShowWindow(_context);
}

NGS_HPP_INLINE void window::hide()
{
	::glfwHideWindow(_context);
}

NGS_HPP_INLINE void window::focus()
{
	::glfwFocusWindow(_context);
}

NGS_HPP_INLINE void window::swap_buffer() const
{
	::glfwSwapBuffers(_context);
}

NGS_HPP_INLINE int window::get_key_state(int key) const
{
	return ::glfwGetKey(_context, key);
}

NGS_HPP_INLINE int window::get_mouse_state(int button) const
{
	return ::glfwGetMouseButton(_context, button);
}

#if defined(VK_VERSION_1_0)

NGS_HPP_INLINE VkSurfaceKHR window::create_surface(VkInstance instance, VkAllocationCallbacks* allocator) const
{
	VkSurfaceKHR surface;
	auto ret = glfwCreateWindowSurface(instance, _context, nullptr, &surface);
	NGS_ASSERT(ret == VK_SUCCESS, "failed to create window surface!");
	return surface;
}

#endif

NGS_LIB_END
