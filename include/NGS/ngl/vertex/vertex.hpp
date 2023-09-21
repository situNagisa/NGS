#pragma once

#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/vertex/array/base.h"

NGL_BEGIN
NGL_BUF_BEGIN

NGS_HPP_INLINE void Vertex::Update() {
	if (_current_vertex_array)
		bind(_current_vertex_array);
	for (auto& buffer : _buffers) {
		buffer->Update();
	}
}

NGS_HPP_INLINE void Vertex::SetVertexArray(objects::VertexArrayBase* vertex_array) {
	_current_vertex_array = vertex_array;
	bind(_current_vertex_array);
	size_t index = 0;
	for (auto& buffer : _buffers) {
		bind(buffer);
		for (auto& attrib : buffer->format.properties) {
			NGL_CHECK(glEnableVertexAttribArray(index));
			NGL_CHECK(glVertexAttribPointer(index, attrib.count, attrib.type, attrib.normalized, buffer->format.size, (void_ptr_cst)attrib.offset));
			index++;
		}
	}
}

NGS_END
NGL_END
