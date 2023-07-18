#pragma once

#include "NGS/ngl/vertex/array/array.h"
#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/shader/shader.h"

NGL_BEGIN
NGL_OBJ_BEGIN

constexpr size_t default_indices_count = size_t(-1);

_NGL_VAO_DERIVED_FROM(VertexArray, IndicesVertexArray) {
public:
	using base = VertexArray<_Buffers...>;
	using element_type = typename base::element_type;

	_IndicesVertexArray(_IndicesVertexArray && other)
		: base(std::move(other))
		, _indices(other._indices)
	{}
	_IndicesVertexArray(size_t count, Usage usage, size_t indices_count = default_indices_count)
		: base(count, usage)
		, _indices(indices_count == default_indices_count ? count : indices_count, usage)
	{}
protected:
	void _AddIndices(size_t count) {
		std::vector<indices_t> indices{};
		for (size_t i = _indices_count; i < _indices_count + count; i++)
		{
			indices.push_back(i);
		}
		_AddIndices(indices);
	}
	template<std::ranges::random_access_range _Rng>
		requires std::convertible_to<std::ranges::range_value_t<_Rng>, indices_t>
	void _AddIndices(_Rng && indices) {
		_indices.Write(std::ranges::cdata(indices), std::ranges::size(indices), _indices_count);
		_indices_count += std::ranges::size(indices);
	}
public:
	template<CBufferRange<element_type> _BufRng>
	void AddVertexes(size_t count, _BufRng && buffers) {
		base::AddVertexes(count, std::forward<_BufRng>(buffers));
		_AddIndices(count);
	}
	void AddVertexes(CVertexRange<element_type> auto && vertexes, size_t count = 0) {
		base::AddVertexes(std::forward<decltype(vertexes)>(vertexes), count);
		_AddIndices(count);
	}
	void AddVertexes(size_t count, _NGL_VAO_BUF_T(buffers, base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	void AddVertexes(size_t count, _NGL_VAO_BUF_VIEW(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	void AddVertexes(size_t count, _NGL_VAO_BUF_CONTAINER(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	virtual void Update()override {
		if (!this->_required_update)return;
		base::Update();
		_indices.Update();
	}
	virtual void Render()override {
		NGS_ASSERT(OpenGL::I().vertex_array->IsState(this));
		if (this->_current_shader)
			OpenGL::I().shader->Select(this->_current_shader);
		_NGL_CHECK(glDrawElements((GLenum)this->_draw_mode, _indices_count, (GLenum)_indices.type, (void_ptr_cst)0));
	}
	virtual void Clear()override {
		base::Clear();
		_indices_count = 0;
	}
protected:
	buffers::Indices _indices;
	size_t _indices_count = 0;
};

NGS_END
NGL_END
