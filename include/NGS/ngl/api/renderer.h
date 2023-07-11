#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

class Window;

class Renderer : public Singleton<Renderer> {
public:

private:
	friend class base;
	Renderer() = default;
public:
	void Viewport(int x, int y, size_t width, size_t height);
	void Viewport(const Rectanglei& range) { Viewport(range.x, range.y, range.width, range.height); }
	void Viewport(const Window& window);

	void Clear(GLbitfield mask);
	void FullColor(StdRGBA rgba);
private:

private:

};

NGL_END
