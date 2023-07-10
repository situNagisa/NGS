#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/gl.h"

NGL_BEGIN

struct DynamicVertex {
	DynamicVertex() = default;
	DynamicVertex(gl::BufferUsage usage, const std::ranges::random_access_range auto& layouts, size_t size)
		: usage(usage)
		, layouts()
		, size(size)
	{
		std::ranges::copy(layouts, std::back_inserter(this->layouts));
	}

	void AddLayout(type_t type, size_t count, size_t size, bool normalized = false, bool enable = true) {
		layouts.emplace_back((layouts.empty() ? 0 : (layouts.back().offset + layouts.back().size)), type, count, size, normalized, enable);
		this->size += size;
	}
	template<CTemplateFrom<gl::layout> _Layout_>
	void AddLayout(bool normalized = false, bool enable = true) {
		AddLayout(_Layout_::tv_bitmap, _Layout_::count, _Layout_::size, normalized, enable);
	}

	gl::BufferUsage usage = gl::BufferUsage::static_draw;
	std::vector<gl::Layout> layouts{};
	size_t size = 0;
};
template<CTemplateFrom<gl::vertex> _Vertex, gl::BufferUsage _Usage = gl::BufferUsage::static_draw>
struct StaticVertex {

	constexpr static gl::BufferUsage usage = _Usage;
	constexpr static std::array<gl::Layout, _Vertex::count> layouts = _Vertex::layouts;
	constexpr static size_t size = _Vertex::size;
};

template<class T>
concept CVertex = requires(T t, const T t_cst) {
	{t_cst.size} -> std::convertible_to<size_t>;
	{t_cst.usage} -> std::convertible_to<gl::BufferUsage>;
		requires std::same_as<std::ranges::range_value_t<decltype(t_cst.layouts)>, gl::Layout>;
		requires std::ranges::sized_range<decltype(t_cst.layouts)>;
};


NGL_END
