#pragma once

#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_BUF_BEGIN

NGS_HPP_INLINE BufferObject::BufferObject(BufferTarget target, void_ptr data, size_t size, Usage usage)
	: target(target)
	, _data(static_cast<byte_ptr>(data))
	, _size(size)
	, _is_reference(true)
	, _update_begin(0)
	, _update_size(size)
	, _usage(usage)
{
	NGL_CHECK(glGenBuffers(1, &_context));
	OpenGL::I().buffer_target->Select(this);
	NGL_CHECK(glBufferData(static_cast<GLenum>(target), size, nullptr, static_cast<GLenum>(usage)));
}
NGS_HPP_INLINE BufferObject::BufferObject(BufferTarget target, size_t size, Usage usage)
	: BufferObject(target, new byte[size](), size, usage)
{
	_is_reference = false;
}
NGS_HPP_INLINE BufferObject::BufferObject(BufferObject&& other)
	: State(std::move(other))
	, target(other.target)
	, _data(other._data)
	, _size(other._size)
	, _is_reference(other._is_reference)
	, _update_begin(other._update_begin)
	, _update_size(other._update_size)
	, _usage(other._usage)
{
	other._data = nullptr;
}

NGS_HPP_INLINE BufferObject::~BufferObject() {
	if (!_context)return;
	NGL_CHECK(glDeleteBuffers(1, &_context));
	if (!_is_reference)delete[] _data;
}

NGS_HPP_INLINE void BufferObject::Update() {
	if (!_required_update)return;
	if (!_update_size)return;
	State::Update();
	NGL_CHECK(glBindBuffer(static_cast<GLenum>(target), _context));
	NGL_CHECK(glBufferSubData(static_cast<GLenum>(target), _update_begin, _update_size, _data));
	_update_begin = _update_size = 0;
}

NGS_HPP_INLINE void BufferObject::View(size_t size, size_t offset) {
	_update_begin = offset;
	_update_size = size;
	RequiredUpdate();
}
#undef min
#undef max

NGS_HPP_INLINE void BufferObject::Write(void_ptr_cst data, size_t size, size_t offset) {
	NGS_ASSERT(offset + size <= _size, "out of range");
	std::memcpy(_data + offset, data, size);
	size_t min = std::min(offset, _update_begin);
	size_t max = std::max(offset + size, _update_begin + _update_size);
	View(max - min, min);
}

NGS_HPP_INLINE void BufferObject::Resize(size_t size)
{
	const auto new_data = new byte[size]();
	std::memcpy(new_data, _data, std::min(_size, size));

	if (!_is_reference) {
		delete[] _data;
	}

	_data = new_data;
	View(size, 0);
	OpenGL::I().buffer_target->Select(this);
	NGL_CHECK(glBufferData(static_cast<GLenum>(target), size, nullptr, static_cast<GLenum>(_usage)));
}

NGS_HPP_INLINE void BufferObject::Resize(size_t size, Usage usage)
{
	_usage = usage;
	Resize(size);
}

NGS_HPP_INLINE void BufferObject::SetUsage(Usage usage)
{
	Resize(_size, usage);
}


NGS_END

NGL_END
