#pragma once

#include "NGL/api/renderer.h"
#include "NGL/gl/gl.h"
#include "NGL/fw/glfw.h"

NGL_BEGIN

NGS_HPP_INLINE void Renderer::Viewport(int x, int y, size_t width, size_t height) { gl::state.Viewport(x, y, width, height); }
NGS_HPP_INLINE void Renderer::Viewport(const Window& window) { auto size = window.GetSize(); Viewport(0, 0, size.x, size.y); }

NGS_HPP_INLINE void Renderer::Clear(GLbitfield mask) { gl::renderer.Clear(mask); }
NGS_HPP_INLINE void Renderer::FullColor(StdRGBA rgba) { gl::renderer.ClearColor(rgba); }

NGL_END
