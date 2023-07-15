#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_BUF_BEGIN

class Buffer : public State {
public:
	/**
	 * @brief
	 *
	 * @param type
	 * @param data
	 * @param size
	 * @param usage
	 */
	Buffer(BufferTarget target, void_ptr data, size_t size, Usage usage);
	/**
	 * @brief
	 *
	 * @param type
	 * @param size
	 * @param usage
	 */
	Buffer(BufferTarget target, size_t size, Usage usage);
	Buffer(Buffer&& other);
	~Buffer();

	virtual void Update()override;
	void View(size_t size, size_t offset);
	void Write(void_ptr_cst data, size_t size, size_t offset);

public:
	const BufferTarget target;
protected:
	byte_ptr _data;
	size_t _size;
	bool _is_reference;
	size_t _update_begin;
	size_t _update_size;
};

NGS_END
NGL_END
