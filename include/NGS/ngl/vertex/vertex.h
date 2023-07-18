#pragma once

#include "NGS/ngl/vertex/vertex_buffer.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class VertexArrayBase;
NGS_END
NGL_BUF_BEGIN

class Vertex : public DeleteCopy {
public:
	using buffer_type = VertexBuffer;

	Vertex(buffer_type** buffers, size_t count)
		: _is_unique(false)
	{
		_buffers.resize(count);
		std::memcpy(_buffers.data(), buffers, count * sizeof(buffer_type*));
	}
	template<std::ranges::range _Rng>
		requires std::same_as<std::ranges::range_value_t<_Rng>, buffer_type*>
	Vertex(_Rng&& buffers)
		: _is_unique(false)
	{
		std::ranges::copy(std::forward<_Rng>(buffers), std::back_inserter(_buffers));
	}
	Vertex(Vertex&& other)
		: _is_unique(other._is_unique)
		, _buffers(std::move(other._buffers))
	{
		other._is_unique = false;
	}

	~Vertex() {
		if (_is_unique) {
			for (auto& buffer : _buffers) {
				delete buffer;
			}
		}
	}
	void SetUnique(bool unique) { _is_unique = unique; }

	void Update();

	void SetVertexArray(objects::VertexArrayBase& vertex_array) { SetVertexArray(&vertex_array); }
	void SetVertexArray(objects::VertexArrayBase* vertex_array);

	const auto& GetAttrib(size_t attrib_index) const{ return _attribs[attrib_index]; }
	size_t GetAttribCount()const { return _attribs.size(); }
	size_t GetBufferCount()const { return _buffers.size(); }

	auto begin() { return _buffers.begin(); }
	auto begin()const { return _buffers.begin(); }
	auto end() { return _buffers.end(); }
	auto end()const { return _buffers.end(); }

	buffer_type& operator[](size_t index) { return *_buffers[index]; }
	const buffer_type& operator[](size_t index)const { return *_buffers[index]; }

	size_t size()const { return _buffers.size(); }
private:
	struct _AttribFormat {
		byte_ptr data;
		const Attrib* format;
		const buffer_type* buffer;
	};

	void _InitAttrib() {
		for (auto& buffer : _buffers) {
			for (auto& attrib : buffer->format.properties) {
				_attribs.push_back(_AttribFormat{ buffer->GetData() + attrib.offset, &attrib,buffer });
			}
		}
	}
private:
	bool _is_unique;
	std::vector<buffer_type*> _buffers{};
	std::vector<_AttribFormat> _attribs{};
	objects::VertexArrayBase* _current_vertex_array = nullptr;
};

NGS_END
NGL_FAC_BEGIN
template<CBuffer... _Buffers>
buffers::Vertex make_vertex(size_t count, Usage usage) {
	buffers::Vertex v{
		std::array<buffers::VertexBuffer*, sizeof...(_Buffers)>{
			(new buffers::VertexBuffer(factories::make_vertex_buffer<_Buffers>(count, usage)))...
			} };
	v.SetUnique(true);
	return v;
}
NGS_END
NGL_END
