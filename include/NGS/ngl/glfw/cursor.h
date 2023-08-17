#pragma once

#include "NGS/ngl/glfw/defined.h"
#include "NGS/ngl/glfw/image.h"
#include "NGS/ngl/enum/cursor.h"

NGL_FW_BEGIN

class NGS_API  Cursor : DeleteCopy{
public:
	using self_type = Cursor;
	using context_type = GLFWcursor*;
public:
	Cursor(CursorShape shape)
		: _context(glfwCreateStandardCursor(static_cast<int>(shape)))
	{}
	Cursor(const Image& image, int x_hot, int y_hot)
		: _context(glfwCreateCursor(&image.GetImage(), x_hot, y_hot))
	{}

	~Cursor() {
		glfwDestroyCursor(_context);
	}

	auto GetContext() { return _context; }
	auto GetContext()const { return _context; }

private:
	context_type _context;
};

NGL_FW_END
