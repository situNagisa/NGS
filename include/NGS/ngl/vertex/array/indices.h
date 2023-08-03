#pragma once

#include "NGS/ngl/vertex/array/array.h"
#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/shader/shader.h"
#include "NGS/ngl/vertex/interface/IIndicesCtrl.h"
#include "NGS/ngl/vertex/ctrl/vertex.h"

NGL_BEGIN
NGL_OBJ_BEGIN

_NGL_VAO_DERIVED_FROM(VertexArray, IndicesVertexArray) {
public:
	using base = VertexArray<_Buffers...>;
	using element_type = typename base::element_type;

	_IndicesVertexArray(_IndicesVertexArray && other)
		: base(std::move(other))
		, _indices_ctrl(std::move(other._indices_ctrl))
	{}
	_IndicesVertexArray(size_t count, Usage usage, std::shared_ptr<IIndicesCtrl> indices_ctrl)
		: base(count, usage)
		, _indices_ctrl(indices_ctrl)
	{}
	_IndicesVertexArray(size_t count, Usage usage)
		: _IndicesVertexArray(count, usage, std::make_shared<VertexIndicesCtrl>(count, usage))
	{}
public:
	void SetIndicesCtrl(const std::shared_ptr<IIndicesCtrl>&indices_ctrl) { _indices_ctrl = indices_ctrl; }

	template<CBufferRange<element_type> _BufRng>
	void AddVertexes(size_t count, _BufRng && buffers) {
		_indices_ctrl->AddSequence(base::_count, count);
		base::AddVertexes(count, std::forward<_BufRng>(buffers));
	}
	void AddVertexes(CVertexRange<element_type> auto && vertexes, size_t count = 0) {
		_indices_ctrl->AddSequence(base::_count, count);
		base::AddVertexes(std::forward<decltype(vertexes)>(vertexes), count);
	}
	void AddVertexes(size_t count, _NGL_VAO_BUF_T(buffers, base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(buffers))...}); }
	void AddVertexes(size_t count, _NGL_VAO_BUF_VIEW(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }
	void AddVertexes(size_t count, _NGL_VAO_BUF_CONTAINER(base) buffers) { AddVertexes(count, std::array<typename base::tag_buffer::type, base::buffer_count>{std::launder(reinterpret_cast<base::tag_buffer::type>(std::ranges::cdata(buffers)))...}); }

	virtual void Update()override {
		if (!this->_required_update)return;
		base::Update();
		_indices_ctrl->GetIndices().Update();
	}
	virtual void Render()override {
		if (!OpenGL::I().vertex_array->IsState(this))
			OpenGL::I().vertex_array->Select(this);
		NGL_CHECK(glDrawElements((GLenum)this->_draw_mode, _indices_ctrl->GetIndicesCount(), (GLenum)_indices_ctrl->GetIndices().type, (void_ptr_cst)0));
	}
	virtual void Clear()override {
		base::Clear();
		_indices_ctrl->Clear();
	}
protected:
	std::shared_ptr<IIndicesCtrl> _indices_ctrl = nullptr;
};

NGS_END
NGL_END
