#pragma once

#include "./window.h"
#include "./state_machine.h"

NGS_EXTERNAL_GLFW_BEGIN

NGS_HPP_INLINE window::window(std::string_view title, const Point2i& size)
	: _title(title)
{
	_context = glfwCreateWindow(size.x, size.y, _title.c_str(), nullptr, nullptr);
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

NGS_HPP_INLINE void window::close() { glfwSetWindowShouldClose(_context, true); }

NGS_HPP_INLINE bool window::is_should_close() const noexcept { return glfwWindowShouldClose(_context); }

NGS_HPP_INLINE void window::should_close() const noexcept { glfwSetWindowShouldClose(_context, GL_TRUE); }

NGS_HPP_INLINE void window::set_title(std::string_view title) {
	_title = title;
	glfwSetWindowTitle(_context, _title.c_str());
}

NGS_HPP_INLINE void window::set_position(int x, int y) { glfwSetWindowPos(_context, x, y); }

NGS_HPP_INLINE Point2i window::get_position() const
{
	int x, y;
	glfwGetWindowPos(_context, &x, &y);
	return { x,y };
}

NGS_HPP_INLINE void window::set_size(int width, int height) { glfwSetWindowSize(_context, width, height); }

NGS_HPP_INLINE Point2i window::get_size() const
{
	int width, height;
	glfwGetWindowSize(_context, &width, &height);
	return { width,height };
}

NGS_HPP_INLINE void window::set_input_mode(int mode, int value) { glfwSetInputMode(_context, mode, value); }

NGS_HPP_INLINE void window::set_cursor(GLFWcursor* cursor)
{
	glfwSetCursor(_context, cursor);
}

NGS_HPP_INLINE void window::set_cursor_position(double x, double y)
{
	glfwSetCursorPos(_context, x, y);
}

NGS_HPP_INLINE Point2d window::get_cursor_position() const
{
	double x, y;
	glfwGetCursorPos(_context, &x, &y);
	return { x,y };
}

NGS_HPP_INLINE Point2i window::get_framebuffer_size() const
{
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(_context, &bufferWidth, &bufferHeight);
	return { bufferWidth,bufferHeight };
}

NGS_HPP_INLINE std::pair<Point2i, Point2i> window::get_frame_size() const
{
	int left, top, right, bottom;
	glfwGetWindowFrameSize(_context, &left, &top, &right, &bottom);
	return { Point2i(top,bottom), Point2i(left,right) };
}

NGS_HPP_INLINE Rectanglei window::get_client_bound() const
{
	auto pos = get_position();
	auto size = get_size();
	return { pos,size };
}

NGS_HPP_INLINE void window::active()
{
	GLFW::instance().select(this);
}

NGS_HPP_INLINE void window::iconify()
{
	glfwIconifyWindow(_context);
}

NGS_HPP_INLINE void window::restore()
{
	glfwRestoreWindow(_context);
}

NGS_HPP_INLINE void window::maximize()
{
	glfwMaximizeWindow(_context);
}

NGS_HPP_INLINE void window::show()
{
	glfwShowWindow(_context);
}

NGS_HPP_INLINE void window::hide()
{
	glfwHideWindow(_context);
}

NGS_HPP_INLINE void window::focus()
{
	glfwFocusWindow(_context);
}

NGS_HPP_INLINE void window::swap_buffer() const
{
	glfwSwapBuffers(_context);
}

NGS_HPP_INLINE int window::get_key_state(int key) const
{
	return glfwGetKey(_context, key);
}

NGS_HPP_INLINE int window::get_mouse_state(int button) const
{
	return glfwGetMouseButton(_context, button);
}

NGS_EXTERNAL_GLFW_END
