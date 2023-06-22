#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/config.h"
#include "NGL/context.h"
#include "NGL/fw/window.h"

NGL_BEGIN

class Window;

class GLFW : public Current<Window, GLFW> {
public:
	NGS_TYPE_DEFINE(Window, window);

private:
	friend class base;
	friend class Constructor;
	GLFW(int major = NGL_OPENGL_MAJOR, int minor = NGL_OPENGL_MINOR);
	static void _SET_CURRENT_CONTEXT(context_type::handle_type window);
public:
	~GLFW();

	void PollEvents();
};
inline static auto glfw = Constructor::Construct<GLFW>();

NGL_END
