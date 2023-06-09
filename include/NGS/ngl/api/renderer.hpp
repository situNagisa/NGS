﻿#pragma once

#include "NGS/ngl/api/renderer.h"
#include "NGS/ngl/gl/gl.h"
#include "NGS/ngl/fw/glfw.h"

NGL_BEGIN

NGS_HPP_INLINE void Renderer::Viewport(int x, int y, size_t width, size_t height) { gl::instance::state.Viewport(x, y, width, height); }
NGS_HPP_INLINE void Renderer::Viewport(const Window& window) { auto size = window.GetSize(); Viewport(0, 0, size.x, size.y); }

NGS_HPP_INLINE void Renderer::Clear(GLbitfield mask) { gl::instance::renderer.Clear(mask); }
NGS_HPP_INLINE void Renderer::FullColor(StdRGBA rgba) { gl::instance::renderer.ClearColor(rgba); }

NGL_END
