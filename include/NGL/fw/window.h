#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/fw/context.h"

NGL_BEGIN

class Window {
public:

private:
	friend class Constructor;
	friend class Destructor;
	Window() : Window("", { 1,1 }) {};
	Window(std::string_view name, const Point2i& size);
	~Window()noexcept;
public:

	bool Open(size_t width, size_t height, std::string_view title);
	bool IsOpened()const;
	void Close();
	bool ShouldClose()const noexcept;

	bool IsPress(int keycode)const noexcept;
	bool IsRelease(int keycode)const noexcept;
	bool IsActive()const;

	void SetTitle(std::string_view title);
	void SetIcon(const std::vector<GLFWimage>& icons);
	void SetPosition(int x, int y);
	void SetPosition(const Point2i& pos) { SetPosition(pos.x, pos.y); }
	void SetSize(int width, int height);
	void SetSize(const Point2i& size) { SetSize(size.x, size.y); }

	GLFWmonitor* GetMonitor()const;
	ngs::Point2i GetFramebufferSize()const;
	ngs::Point2i GetPosition()const;
	ngs::Point2i GetSize()const;
	Rectangle<int> GetBounds()const;

	void Iconify();
	void Restore();
	void Maximize();
	void Show();
	void Hide();
	void Focus();
	void Active();

	void SwapBuffer()const;

	friend class _GLFW;
	friend class GLFW;

	const GLFW_Context& GetContext()const { return _context; }
private:
	GLFW_Context _context = nullptr;
	void_ptr _data = nullptr;
};

NGL_END
