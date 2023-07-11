#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl/gl.h"
#include "NGS/ngl/api/vertex.h"

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

class VertexArrayBuffer {
public:

private:
	friend class VertexArray;
	VertexArrayBuffer(size_t max_count, const CVertex auto& vertex)
		: vertex(vertex.usage, vertex.layouts, vertex.size)
		, _buffer(nullptr)
		, _max_count(max_count)
		, _count(0)
		, _is_reference(false)
	{
		NGS_NEW_ARR(_buffer, max_count * vertex.size, byte)();
		_Construct();
	}
	VertexArrayBuffer(void_ptr buffer, size_t capacity, const CVertex auto& vertex)
		: vertex(vertex.usage, vertex.layouts, vertex.size)
		, _buffer((byte_ptr)buffer)
		, _max_count(capacity / vertex.size)
		, _count(_max_count)
		, _is_reference(true)
	{
		NGS_ASSERT(capacity % vertex.size == 0);
		_Construct();
	}
	VertexArrayBuffer(std::ranges::random_access_range auto& buffer, const CVertex auto& vertex)
		: VertexArrayBuffer(std::ranges::data(buffer), std::ranges::size(buffer) * sizeof(std::ranges::range_value_t<decltype(buffer)>), vertex)
	{}
public:
	~VertexArrayBuffer() {
		if (!_is_reference) {
			NGS_DELETE_ARR(_buffer);
		}
	}

	void Active() { gl::array_buffer.PushContext(_context); }
	bool IsActive()const { return gl::array_buffer.IsContext(_context); }
	void Deactivate() { gl::array_buffer.PopContext(); }

	indices_t AddVertex(void_ptr_cst buffer) {
		indices_t indices = _count;
		std::memcpy(_buffer + _count * vertex.size, buffer, vertex.size);
		_count++;
		return indices;
	}
	void UpdateData(size_t offset, size_t count) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(offset + count <= _max_count, Format("the 'end'(offset + count = %d) out of range([0,%d])", offset + count, _max_count));
		gl::array_buffer.UpdateData(_buffer, offset * vertex.size, count * vertex.size);
	}
	void UpdateData(size_t count) { UpdateData(0, count); }
	void UpdateData() { UpdateData(0, _count); }

	size_t GetMaxCount()const { return _max_count; }
	size_t GetCount()const { return _count; }

	byte_ptr GetData() { return _buffer; }
	byte_ptr_cst GetData()const { return _buffer; }
public:
	const DynamicVertex vertex;
private:
	void _Construct() {
		Active();
		gl::array_buffer.SetData(_buffer, _max_count * vertex.size, vertex.usage);
	}

	bool _IsContext()const {
		if (!IsActive()) return false;
		return true;
	}
private:
	byte_ptr _buffer;
	size_t _max_count = 0;
	size_t _count = 0;
	bool _is_reference = false;

	gl::ArrayBufferContext _context{};
};

//class VertexArrayBuffer {
//private:
//	friend class VertexArray;
//	VertexArrayBuffer() = default;
//public:
//
//	void Active() {
//		gl::array_buffer.PushContext(_context);
//		gl::element_buffer.PushContext(_element_buffer_context);
//	}
//	void Deactivate() {
//		gl::array_buffer.PopContext();
//		gl::element_buffer.PopContext();
//	}
//
//	template<CTemplateFrom<gl::vertex> _Layout>
//	void SetBuffer(void_ptr_cst buffer, size_t size, gl::BufferUsage usage = gl::BufferUsage::static_draw, bool normalized = false, bool enable = true) {
//		NGS_ASSERT(_IsContext());
//		gl::array_buffer.SetData(buffer, size, usage);
//		gl::array_buffer.SetAttribPointer<_Layout>(normalized, enable);
//	}
//	template<CTemplateFrom<gl::vertex> _Layout>
//	void SetBuffer(const std::ranges::random_access_range auto& range, gl::BufferUsage usage = gl::BufferUsage::static_draw, bool normalized = false, bool enable = true) {
//		SetBuffer<_Layout>(std::ranges::cdata(range), std::ranges::size(range) * sizeof(std::ranges::range_value_t<decltype(range)>), usage, normalized, enable);
//	}
//
//	template<CTemplateFrom<gl::vertex> _Layout>
//	void SetBuffer(const VertexBuffer<_Layout>& buffer, gl::BufferUsage usage = gl::BufferUsage::static_draw, bool normalized = false, bool enable = true) {
//		NGS_ASSERT(_IsContext());
//		auto& data = buffer.GetContainer();
//		SetBuffer<_Layout>(std::ranges::cdata(data), std::ranges::size(data), usage, normalized, enable);
//		gl::element_buffer.SetData(buffer.GetIndices(), usage);
//		_indices_count = buffer.GetIndices().size();
//	}
//
//	void Draw() {
//		gl::array_buffer.DrawElements<indices_t>(gl::BufferDrawMode::triangles, _indices_count, 0);
//	}
//private:
//	bool _IsContext()const {
//		if (!gl::array_buffer.IsContext(_context)) return false;
//		if (!gl::element_buffer.IsContext(_element_buffer_context)) return false;
//		return true;
//	}
//private:
//	gl::ArrayBufferContext _context = {};
//	gl::ElementBufferContext _element_buffer_context = {};
//	size_t _indices_count = 0;
//};

class VertexArray {
public:
	~VertexArray() {
		for (auto buffer : _buffers) {
			NGS_DELETE(buffer);
		}
	}

	void Active() { gl::vertex_array.PushContext(_context); }
	bool IsActive()const { return gl::vertex_array.IsContext(_context); }
	void Deactivate() { gl::vertex_array.PopContext(); }

	VertexArrayBuffer& AddBuffer(size_t max_count, const CVertex auto& vertex) {
		VertexArrayBuffer* vertex_buffer;
		NGS_NEW(vertex_buffer, VertexArrayBuffer)(max_count, vertex);
		_ContactBuffer(*vertex_buffer);
		_buffers.push_back(vertex_buffer);
		return *vertex_buffer;
	}
	template<CTemplateFrom<gl::vertex> _Vertex, gl::BufferUsage _Usage = gl::BufferUsage::static_draw>
	VertexArrayBuffer& AddBuffer(size_t max_count) { return AddBuffer(max_count, StaticVertex<_Vertex, _Usage>{}); }
	VertexArrayBuffer& AddBuffer(void_ptr buffer, size_t capacity, const CVertex auto& vertex) {
		VertexArrayBuffer* vertex_buffer;
		NGS_NEW(vertex_buffer, VertexArrayBuffer)(buffer, capacity, vertex);
		_ContactBuffer(*vertex_buffer);
		_buffers.push_back(vertex_buffer);
		return *vertex_buffer;
	}
	template<CTemplateFrom<gl::vertex> _Vertex, gl::BufferUsage _Usage = gl::BufferUsage::static_draw>
	VertexArrayBuffer& AddBuffer(void_ptr buffer, size_t capacity) { return AddBuffer(buffer, capacity, StaticVertex<_Vertex, _Usage>{}); }
	VertexArrayBuffer& AddBuffer(std::ranges::random_access_range auto& buffer, const CVertex auto& vertex) {
		VertexArrayBuffer* vertex_buffer;
		NGS_NEW(vertex_buffer, VertexArrayBuffer)(buffer, vertex);
		_ContactBuffer(*vertex_buffer);
		_buffers.push_back(vertex_buffer);
		return *vertex_buffer;
	}
	/**
	 * @brief 添加一个顶点缓冲区至顶点数组
	 *
	 * @tparam _Vertex 顶点类型，请使用`gl::vertex`或`gl::vertex_vector`构建
	 * @param buffer 顶点缓冲区，满足`std::ranges::random_access_range`概念
	 *
	 * @warning 返回的顶点缓冲区的生命周期与顶点数组相同，且顶点缓冲区处于活动状态，由于NGL中活动状态是栈结构，
	 *			如果希望连续添加缓冲区，请使用完该函数后立即调用`VertexArrayBuffer::Deactivate`函数
	 *
	 * @return `VertexArrayBuffer&` 返回顶点缓冲区
	 */
	template<CTemplateFrom<gl::vertex> _Vertex, gl::BufferUsage _Usage = gl::BufferUsage::static_draw>
	VertexArrayBuffer& AddBuffer(std::ranges::random_access_range auto& buffer) { return AddBuffer(buffer, StaticVertex<_Vertex, _Usage>{}); }

	auto& GetBuffers() { return _buffers; }
	const auto& GetBuffers()const { return _buffers; }

	void DrawArrays(gl::DrawMode mode, size_t offset, size_t count) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(offset + count <= _GetLayoutCount());
		gl::vertex_array.DrawArrays(mode, offset, count);
	}
	void DrawArrays(gl::DrawMode mode, size_t count) { DrawArrays(mode, 0, count); }
	void DrawArrays(gl::DrawMode mode) { DrawArrays(mode, 0, _GetLayoutCount()); }

	void UpdateData(size_t offset, size_t count) {
		for (auto buffer : _buffers) {
			buffer->Active();
			buffer->UpdateData(offset, count);
			buffer->Deactivate();
		}
	}
	void UpdateData(size_t count) { UpdateData(0, count); }
	void UpdateData() { UpdateData(0, _GetVertexCount()); }
private:
	void _ContactBuffer(VertexArrayBuffer& buffer) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(buffer.IsActive());
		NGS_ASSERT(!buffer.vertex.layouts.empty());
		NGS_DEBUG_EXPR(if (!_buffers.empty())NGS_ASSERT(_GetVertexCount() == buffer.GetMaxCount()));

		size_t offset = _GetOffset();

		for (size_t i = 0; i < buffer.vertex.layouts.size(); i++)
		{
			const auto& layout = buffer.vertex.layouts[i];
			size_t index = i + offset;
			gl::vertex_array.SetAttribPointer(index, layout.count, layout.offset, layout.type, buffer.vertex.size, layout.normalized);
			if (layout.enable)gl::vertex_array.Enable(index);
		}
	}

	size_t _GetOffset() const {
		size_t offset{};
		for (auto buffer : _buffers) {
			offset += buffer->vertex.size;
		}
		return offset;
	}
	size_t _GetLayoutCount() const {
		size_t count{};
		for (auto buffer : _buffers) {
			count += buffer->vertex.layouts.size();
		}
		return count;
	}
	size_t _GetVertexCount()const { return _buffers.back()->GetMaxCount(); }
private:
	gl::VertexArrayContext _context{};
	std::vector<VertexArrayBuffer*> _buffers;
};

NGL_END
