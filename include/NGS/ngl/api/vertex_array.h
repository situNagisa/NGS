#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl/gl.h"
#include "NGS/ngl/api/vertex.h"

NGL_BEGIN

_NGS_TYPE_DEFINE(uint32, indices_t);

template<size_t _CapacityCount>
class Vertex : public gl::Vertex {
public:

	Vertex(Usage usage, const_iterator begin, size_t count, size_t size)
		: gl::Vertex(usage, begin, count, size)
		, _data(nullptr)
		, _is_reference(false)
	{
		NGS_NEW_ARR(_data, capacity(), byte);
	}
	Vertex(Usage usage, const_iterator begin, size_t count, size_t size, void_ptr data)
		: gl::Vertex(usage, begin, count, size)
		, _data((byte_ptr)data)
		, _is_reference(true)
	{}
	~Vertex() {
		if (_is_reference)return;
		NGS_DELETE_ARR(_data);
	}
public:
	void Initialize() {
		NGS_ASSERT(IsActive());
		gl::instance::array_buffer.SetData(_data, capacity(), usage);
	}

	byte_ptr data() { return _data; }
	byte_ptr_cst data()const { return _data; }

	size_t capacity()const { return _CapacityCount * step(); }
	size_t capacity_count()const { return _CapacityCount; }

	void Active() { gl::instance::array_buffer.SetContext(_context); }
	bool IsActive()const { return gl::instance::array_buffer.IsContext(_context); }
	void Deactivate() { gl::instance::array_buffer.SetContextNull(); }

	void UpdateData(size_t offset, size_t count) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(offset + count <= capacity_count(), Format("the 'end'(offset + count = %d) out of range([0,%d])", offset + count, capacity_count()));
		gl::instance::array_buffer.UpdateData(_data, offset * step(), count * step());
	}
	void UpdateData(size_t count) { UpdateData(0, count); }

	void Write(byte_ptr_cst write_data, size_t count, size_t offset = 0) {
		NGS_ASSERT(offset + count <= capacity_count(), Format("the 'end'(offset + count = %d) out of range([0,%d])", offset + count, capacity_count()));
		std::memcpy(_data + offset * step(), write_data, count * step());
	}
	void Write(const std::ranges::random_access_range auto& write_data, size_t offset = 0) {
		NGS_ASSERT(std::ranges::size(write_data) * sizeof(std::ranges::range_value_t<decltype(write_data)>) % step() == 0);
		Write(
			std::ranges::cdata(write_data),
			std::ranges::size(write_data) * sizeof(std::ranges::range_value_t<decltype(write_data)>) / step(),
			offset
		);
	}
private:
	byte_ptr _data = nullptr;
	bool _is_reference = false;

	gl::ArrayBufferContext _context{};
};

template<size_t _CapacityCount>
class Indices {
public:
	constexpr static size_t step = sizeof(indices_t);
	constexpr static size_t capacity_count = _CapacityCount;
public:
	void Initialize(Usage usage) {
		NGS_ASSERT(IsActive());
		gl::instance::element_buffer.SetData(_indices, usage);
	}

	void Active() { gl::instance::element_buffer.SetContext(_context); }
	bool IsActive()const { return gl::instance::element_buffer.IsContext(_context); }
	void Deactivate() { gl::instance::element_buffer.SetContextNull(); }

	void UpdateData(size_t offset, size_t count) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(offset + count <= capacity_count, Format("the 'end'(offset + count = %d) out of range([0,%d])", offset + count, capacity_count));
		if (!_requires_update)return;
		gl::instance::element_buffer.UpdateData(_indices.data(), offset * step, count * step);
		_requires_update = false;
	}
	void UpdateData(size_t count) { UpdateData(0, count); }
	void UpdateData() { UpdateData(0, _indices_count); }

	void Write(indices_t_ptr_cst write_data, size_t count, size_t offset) {
		NGS_ASSERT(IsActive());
		NGS_ASSERT(offset + count <= capacity_count, Format("the 'end'(offset + count = %d) out of range([0,%d])", offset + count, capacity_count));
		std::memcpy(_indices.data() + offset, write_data, count * step);
		_indices_count += count;
		_requires_update = true;
	}
	void Write(indices_t_ptr_cst write_data, size_t count) {
		Write(write_data, count, _indices_count);
	}
	void Write(indices_t indice) {
		Write(&indice, 1);
	}
	template<std::ranges::random_access_range _Rng>
		requires std::same_as<indices_t, std::ranges::range_value_t<_Rng>>
	void Write(_Rng&& write_data, size_t offset) {
		NGS_ASSERT(std::ranges::size(write_data) * sizeof(std::ranges::range_value_t<decltype(write_data)>) % step == 0);
		Write(
			std::ranges::cdata(write_data),
			std::ranges::size(write_data),
			offset
		);
	}
	template<std::ranges::random_access_range _Rng>
		requires std::same_as<indices_t, std::ranges::range_value_t<_Rng>>
	void Write(_Rng&& write_data) {
		Write(write_data, _indices_count);
	}

	void Clear() {
		_indices_count = 0;
		_requires_update = false;
	}

	size_t size()const { return _indices_count; }
private:
	std::array<indices_t, capacity_count> _indices{};
	size_t _indices_count = 0;

	bool _requires_update = false;

	gl::ElementBufferContext _context{};
};

template<class, class, class, class, class...>
class _VertexArray;

template<size_t _CapacityCount, CTemplateFrom<gl::vertex> _Vertex, CTemplateFrom<gl::vertex>... _Vertexs, size_t... _VertexIt, size_t... _LayoutIt>
class _VertexArray<
	std::integral_constant<size_t, _CapacityCount>,
	std::index_sequence<_VertexIt...>,
	std::index_sequence<_LayoutIt...>,
	_Vertex,
	_Vertexs...
> {
private:
	using _vertex_sequence = boost::mpl::vector<_Vertex, _Vertexs...>;
public:
	constexpr static size_t vertex_capacity_count = _CapacityCount;
	constexpr static size_t triangle_capacity_count = vertex_capacity_count > 2 ? (vertex_capacity_count - 2) : 0;
	constexpr static size_t indices_capacity_count = vertex_capacity_count > 2 ? 3 * triangle_capacity_count : vertex_capacity_count;

	using vertex_array_type = gl::vertex<_Vertex, _Vertexs...>;
	using vertex_type = Vertex<vertex_capacity_count>;
	constexpr static size_t vertex_count = 1 + sizeof...(_Vertexs);

	template<size_t _Index> using vertex_at_t = typename boost::mpl::at_c<_vertex_sequence, _Index>::type;
	template<size_t _Index> using vertex_element_t = typename vertex_at_t<_Index>::template layout_at_t<0>::element_type;
	template<size_t _Index> using vertex_param_t = const vertex_element_t<_Index>*;
	template<size_t _Index> constexpr static size_t_ptr_cst vertex_layout_offset_ptr = vertex_at_t<_Index>::layout_offsets.data();

	constexpr static std::array<size_t_ptr, vertex_count> vertex_layout_offsets = []<size_t... I>(std::index_sequence<I...>) {
		return std::array<size_t_ptr, vertex_count>{const_cast<size_t_ptr>(vertex_layout_offset_ptr<I>)...};
	}(std::make_index_sequence<vertex_count>{});

	template<size_t _Index> using layout_at_t = vertex_array_type::template layout_at_t<_Index>;
	constexpr static size_t layout_count = (_Vertex::layout_count + ... + _Vertexs::layout_count);


	_VertexArray(Usage usage) {
		((_vertexes[_VertexIt] = new vertex_type(
			usage,
			vertex_at_t<_VertexIt>::layouts.data(),
			vertex_at_t<_VertexIt>::layouts.size(),
			vertex_at_t<_VertexIt>::size
		)), ...);
		_Initialize(usage);
	}
	~_VertexArray() {
		for (auto& vertex : _vertexes) {
			delete vertex;
		}
	}

	void Active() { gl::instance::vertex_array.PushContext(_context); }
	bool IsActive()const { return gl::instance::vertex_array.IsContext(_context); }
	void Deactivate() { gl::instance::vertex_array.PopContext(); }

	bool IsEmpty()const { return _vertex_count == 0; }
	bool IsFull()const { return _vertex_count == vertex_capacity_count; }

	indices_t AddVertex(
		const vertex_param_t<_VertexIt>&... vertex
	) {
		size_t index = _vertex_count;
		((_vertexes[_VertexIt]->Write((byte_ptr_cst)vertex, 1, _vertex_count)), ...);
		_vertex_count++;
		return index;
	}
	template<size_t N>
		requires (N >= 3)
	void AddPolygon(const vertex_param_t<_VertexIt>&... va) {
		std::vector<indices_t> indices{};
		for (size_t i = 0; i < N; i++)
		{
			indices.push_back(AddVertex((va + i * vertex_at_t<_VertexIt>::element_count)...));
		}
		_AddPolygon(indices);
	}

	void AddTriangle(const vertex_param_t<_VertexIt>&... va) { AddPolygon<3>(va...); }
	void AddQuad(const vertex_param_t<_VertexIt>&... va) { AddPolygon<4>(va...); }

	void Draw() {
		NGS_ASSERT(IsActive());
		gl::instance::vertex_array.DrawTriangles<indices_t>(_indices.size());
	}
	void Draw(DrawMode mode) {
		NGS_ASSERT(IsActive());
		gl::instance::vertex_array.DrawArrays(mode, 0, _vertex_count);
	}

	void UpdateData(size_t offset, size_t count) {
		for (auto& vertex : _vertexes) {
			vertex->Active();
			vertex->UpdateData(offset, count);
		}
		_indices.Active();
		_indices.UpdateData();
	}
	void UpdateData(size_t count) { UpdateData(0, count); }
	void UpdateData() { UpdateData(0, _vertex_count); }

	void Clear() {
		_vertex_count = 0;
		_indices.Clear();
	}
	//========================
	// container
	//========================

	constexpr bool empty()const { return size(); }

	auto begin() { return _vertexes.begin(); }
	auto begin()const { return _vertexes.begin(); }
	auto end() { return _vertexes.end(); }
	auto end()const { return _vertexes.end(); }

	vertex_type& operator[](size_t n) { return *_vertexes[n]; }
	const vertex_type& operator[](size_t n)const { return *_vertexes[n]; }

	vertex_type& at(size_t n) { *_vertexes.at(n); }
	const vertex_type& at(size_t n) const { *_vertexes.at(n); }
	size_t size() const { return _vertexes.size(); }

	size_t capacity()const { return vertex_capacity_count; }
private:
	void _Initialize(Usage usage) {
		Active();
		size_t index = 0;
		for (size_t i = 0; i < vertex_count; i++)
		{
			auto& vertex = *_vertexes[i];
			vertex.Active();
			vertex.Initialize();
			for (size_t j = 0; j < vertex.size(); j++)
			{
				auto& layout = vertex[j];
				gl::instance::vertex_array.SetAttribPointer(
					index,
					vertex_array_type::layout_counts[index],
					vertex_layout_offsets[i][j],
					vertex_array_type::layout_tv_bitmaps[index],
					vertex.step(),
					layout.normalized
				);
				if (layout.enable)gl::instance::vertex_array.Enable(index);
				index++;
			}
		}
		_indices.Active();
		_indices.Initialize(usage);
		Deactivate();
	}

	void _AddPolygon(std::same_as<indices_t>auto... indice) {
		std::vector<indices_t> indices{indice...};
		_AddPolygon(indices);
	}
	void _AddPolygon(const std::vector<indices_t>& indices) {
		NGS_ASSERT(IsActive());

		for (size_t i = 1; i < indices.size() - 1; i++)
		{
			_indices.Write(indices[0]);
			_indices.Write(indices[i]);
			_indices.Write(indices[i + 1]);
		}
	}
public:
	std::array<vertex_type*, vertex_count> _vertexes{};
	size_t _vertex_count = 0;

	gl::VertexArrayContext _context{};
	Indices<indices_capacity_count> _indices{};
};

template<size_t _CapacityCount, CTemplateFrom<gl::vertex> _Vertex, CTemplateFrom<gl::vertex>... _Vertexs>
using VertexArray = _VertexArray <
	std::integral_constant<size_t, _CapacityCount>,
	std::make_index_sequence<(1 + sizeof...(_Vertexs))>,
	std::make_index_sequence<(_Vertex::layout_count + ... + _Vertexs::layout_count)>,
	_Vertex, _Vertexs...>;

NGL_END
