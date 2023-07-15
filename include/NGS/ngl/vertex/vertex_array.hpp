#pragma once

#include "NGS/ngl/vertex/vertex_array.h"

NGL_BEGIN

NGL_TARGET_BEGIN

NGS_HPP_INLINE void VertexArray::_Select(state_type* state) { _NGL_CHECK(glBindVertexArray(state->GetContext())); }

NGS_END

NGL_OBJ_BEGIN

NGS_HPP_INLINE VertexArray::VertexArray(buffers::Vertex** vertices, size_t count, bool is_reference = true)
	: _is_reference(is_reference)
{
	std::ranges::copy(std::span<buffers::Vertex*>(vertices, count), std::back_inserter(_vertices));
	_NGL_CHECK(glGenVertexArrays(1, &_context));
	OpenGL::I().vertex_array->Select(this);
	size_t index = 0;
	for (auto& vertex : _vertices) {
		OpenGL::I().buffer_target->Select(vertex);
		for (auto& prop : vertex->format.properties) {
			_NGL_CHECK(glEnableVertexAttribArray(index));
			_NGL_CHECK(glVertexAttribPointer(index, prop.size, prop.type, prop.normalized, vertex->format.size, (void_ptr_cst)prop.offset));
			index++;
		}
	}
}
NGS_HPP_INLINE VertexArray::~VertexArray() {
	if (!_context)return;
	_NGL_CHECK(glDeleteVertexArrays(1, &_context));
	if (!_is_reference) {
		for (auto& vertex : _vertices) {
			delete vertex;
		}
	}
}

NGS_HPP_INLINE void VertexArray::AddVertexes(const void_ptr_cst* data_ptr, size_t count)
{
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i]->Write(data_ptr[i], count, _count);
	}
	_count += count;
	RequiredUpdate();
}

NGS_HPP_INLINE void VertexArray::Update() {
	//if (!_required_update)return;
	Object::Update();
	OpenGL::I().vertex_array->Select(this);
	for (auto& vertex : _vertices) {
		vertex->Update();
	}
	_Render();
}

NGS_HPP_INLINE void VertexArray::_Render() {
	_NGL_CHECK(glDrawArrays((GLenum)_draw_mode, _offset, _count));
}

NGS_END

NGL_END
