#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/gl.h"

NGL_BEGIN

using indices_t = uint32;

template<CTemplateFrom<gl::vertex> _Layout>
class VertexBuffer;

template<CTemplateFrom<gl::layout>... _Layouts>
class VertexBuffer<gl::vertex<_Layouts...>> {
private:
	NGS_TYPE_DEFINE(gl::vertex<_Layouts...>, vertex);

	template<CTemplateFrom<gl::layout> _LayoutUnit, class = std::make_index_sequence<_LayoutUnit::count>>
	struct _Unit;

	template<CTemplateFrom<gl::layout> _LayoutUnit, size_t... _I>
	struct _Unit<_LayoutUnit, std::index_sequence<_I...>> {
		template<size_t>
		using element_type = typename _LayoutUnit::element_type;

		template<std::ranges::random_access_range _Rng>
			requires std::same_as<std::ranges::range_value_t<_Rng>, typename _LayoutUnit::element_type>
		_Unit(const _Rng&& unit) {
			NGS_ASSERT(std::ranges::size(unit) == _LayoutUnit::count);
			std::memcpy(data, std::ranges::cdata(unit), sizeof(data));
		}
		constexpr _Unit(element_type<_I>... elements) : data{ elements... } {}

		typename _LayoutUnit::element_type data[_LayoutUnit::count];
	};
public:

	indices_t AddVertex(_Unit<_Layouts>... units) {
		byte_ptr layout_start = nullptr;
		{
			size_t size = _data.size();
			_data.resize(size + __vertex::size);
			layout_start = _data.data() + size;
		}
		size_t i = 0;
		((std::memcpy((layout_start + __vertex::offsets[i]), units.data, __vertex::template sizes[i]), ++i), ...);
		NGS_ASSERT(_data.size() % __vertex::size == 0);
		return indices_t((_data.size() / __vertex::size) - 1);
	}
	void AddTriangle(indices_t i1, indices_t i2, indices_t i3) {
		_indices.push_back(i1);
		_indices.push_back(i2);
		_indices.push_back(i3);
	}

	void AddTriangle(_Unit<_Layouts>... units1, _Unit<_Layouts>... units2, _Unit<_Layouts>... units3) {
		AddTriangle(AddVertex(units1...), AddVertex(units2...), AddVertex(units3...));
	}
	void AddQuad(_Unit<_Layouts>... left_top, _Unit<_Layouts>... right_top, _Unit<_Layouts>... left_down, _Unit<_Layouts>... right_down) {
		size_t lt = AddVertex(left_top...);
		size_t rt = AddVertex(right_top...);
		size_t ld = AddVertex(left_down...);
		size_t rd = AddVertex(right_down...);

		AddTriangle(lt, rt, ld);
		AddTriangle(rt, ld, rd);
	}

	byte_ptr GetData() { return _data.data(); }
	byte_ptr_cst GetData()const { return _data.data(); }

	size_t GetSize()const { return _data.size(); }

	const std::vector<byte>& GetContainer()const { return _data; }
	const std::vector<indices_t>& GetIndices()const { return _indices; }
private:

private:
	std::vector<byte> _data = {};
	std::vector<indices_t> _indices = {};
};

class VertexArray {
public:

	void Active() {
		gl::vertex_array.PushContext(_context);
		gl::array_buffer.PushContext(_array_buffer_context);
		gl::element_buffer.PushContext(_element_buffer_context);
	}
	void Deactivate() {
		gl::vertex_array.PopContext();
		gl::array_buffer.PopContext();
		gl::element_buffer.PopContext();
	}

	template<CTemplateFrom<gl::vertex> _Layout>
	void SetBuffer(const VertexBuffer<_Layout>& buffer, gl::BufferUsage usage = gl::BufferUsage::static_draw, bool normalized = false, bool enable = true) {
		NGS_ASSERT(_IsContext());
		auto& data = buffer.GetContainer();
		gl::array_buffer.SetData(std::ranges::cdata(data), std::ranges::size(data), usage);
		gl::array_buffer.SetAttribPointer<_Layout>(normalized, enable);
		gl::element_buffer.SetData(buffer.GetIndices(), usage);
		_indices_count = buffer.GetIndices().size();
	}

	void Draw() {
		gl::array_buffer.DrawElements<indices_t>(gl::BufferDrawMode::triangles, _indices_count, 0);
	}
private:
	bool _IsContext()const {
		if (!gl::vertex_array.IsContext(_context)) return false;
		if (!gl::array_buffer.IsContext(_array_buffer_context)) return false;
		if (!gl::element_buffer.IsContext(_element_buffer_context)) return false;
		return true;
	}
private:
	gl::VertexArrayContext _context = {};
	gl::ArrayBufferContext _array_buffer_context = {};
	gl::ElementBufferContext _element_buffer_context = {};
	size_t _indices_count = 0;
};


NGL_END
