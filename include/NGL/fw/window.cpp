#include "NGL/fw/window.h"
#include "NGL/opengl.h"

NGL_BEGIN


struct _WindowData {
	Rectangle<int> bounds = {};
	Point2i framebuffer_size = {};
};

static std::unordered_map<GLFWwindow*, std::pair<Window*, _WindowData*>> _s_window_callback_map = {};

static void _sFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	auto& data = *_s_window_callback_map.at(window).second;
	data.framebuffer_size.Set(width, height);
}
static void _sWindowSizeCallback(GLFWwindow* window, int width, int height) {
	auto& data = *_s_window_callback_map.at(window).second;
	data.bounds.width = width;
	data.bounds.height = height;
}
static void _sWindowPosCallback(GLFWwindow* window, int xpos, int ypos) {
	auto& data = *_s_window_callback_map.at(window).second;
	data.bounds.x = xpos;
	data.bounds.y = ypos;
}
NGS_HPP_INLINE Window::Window(std::string_view name, const Point2i& size)
{
	NGS_NEW(_data, _WindowData)();
	auto& data = *reinterpret_cast<_WindowData*>(_data);

	_handle = glfwCreateWindow(size.x, size.y, name.data(), nullptr, nullptr);
	NGS_ASSERT(_handle, "Failed to create GLFW window");

	auto pos = GetPosition();
	data.bounds.Set(pos.x, pos.y, size.x, size.y);
	NGS_ASSERT(!_s_window_callback_map.contains(_handle));
	_s_window_callback_map[_handle] = { this,&data };

	glfwSetFramebufferSizeCallback(_handle, _sFrameBufferSizeCallback);
	glfwSetWindowSizeCallback(_handle, _sWindowSizeCallback);
	glfwSetWindowPosCallback(_handle, _sWindowPosCallback);
}

NGS_HPP_INLINE Window::~Window() noexcept
{
	auto& data = *reinterpret_cast<_WindowData*>(_data);

	glfwDestroyWindow(_handle);
	_s_window_callback_map.erase(_handle);
	NGS_DELETE(&data);
	_data = nullptr;
}
NGS_HPP_INLINE bool Window::Open(size_t width, size_t height, std::string_view title)
{
	SetSize(width, height);
	SetTitle(title);
	Show();
	return true;
}
NGS_HPP_INLINE bool Window::IsOpened() const { return true; }
NGS_HPP_INLINE void Window::Close() {}
NGS_HPP_INLINE bool Window::ShouldClose() const noexcept { return glfwWindowShouldClose(_handle); }

NGS_HPP_INLINE bool Window::IsPress(int keycode)const noexcept { return glfwGetKey(_handle, keycode) == GLFW_PRESS; }
NGS_HPP_INLINE bool Window::IsRelease(int keycode)const noexcept { return glfwGetKey(_handle, keycode) == GLFW_RELEASE; }

NGS_HPP_INLINE void Window::SetTitle(std::string_view title) { glfwSetWindowTitle(_handle, title.data()); }
//NGS_HPP_INLINE void Window::SetIcon(const std::vector<GLFWimage>& icons) { glfwSetWindowIcon(_handle, icons.size(), icons.data()); }
NGS_HPP_INLINE void Window::SetPosition(int x, int y) { glfwSetWindowPos(_handle, x, y); }
NGS_HPP_INLINE void Window::SetSize(int width, int height) { glfwSetWindowSize(_handle, width, height); }

NGS_HPP_INLINE GLFWmonitor* Window::GetMonitor() const { return glfwGetWindowMonitor(_handle); }
NGS_HPP_INLINE ngs::Point2i Window::GetFramebufferSize() const
{
	auto& data = *reinterpret_cast<_WindowData*>(_data);
	int width, height;
	glfwGetFramebufferSize(_handle, &width, &height);
	data.framebuffer_size.Set(width, height);
	return { width,height };
}

NGS_HPP_INLINE ngs::Point2i Window::GetPosition() const
{
	auto& data = *reinterpret_cast<_WindowData*>(_data);
	int x, y;
	glfwGetWindowPos(_handle, &x, &y);
	data.bounds.x = x;
	data.bounds.y = y;
	return { x,y };
}

NGS_HPP_INLINE ngs::Point2i Window::GetSize() const
{
	auto& data = *reinterpret_cast<_WindowData*>(_data);
	int width, height;
	glfwGetWindowSize(_handle, &width, &height);
	data.bounds.width = width;
	data.bounds.height = height;
	return { width,height };
}
NGS_HPP_INLINE Rectangle<int> Window::GetBounds()const { return reinterpret_cast<_WindowData*>(_data)->bounds; }

NGS_HPP_INLINE void Window::Iconify() { glfwIconifyWindow(_handle); }
NGS_HPP_INLINE void Window::Restore() { glfwRestoreWindow(_handle); }
NGS_HPP_INLINE void Window::Maximize() { glfwMaximizeWindow(_handle); }
NGS_HPP_INLINE void Window::Show() { glfwShowWindow(_handle); }
NGS_HPP_INLINE void Window::Hide() { glfwHideWindow(_handle); }
NGS_HPP_INLINE void Window::Focus() { glfwFocusWindow(_handle); }
NGS_HPP_INLINE void Window::SwapBuffer() const { glfwSwapBuffers(_handle); }

NGL_END
