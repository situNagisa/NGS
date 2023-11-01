#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_BUF_BEGIN

class NGS_DLL_API  BufferObject : public State {
public:
	/**
	 * @brief
	 *
	 * @param target
	 * @param data
	 * @param size
	 * @param usage
	 */
	BufferObject(BufferTarget target, void_ptr data, size_t size, Usage usage);
	/**
	 * @brief
	 *
	 * @param target
	 * @param size
	 * @param usage
	 */
	BufferObject(BufferTarget target, size_t size, Usage usage);
	BufferObject(BufferObject&& other);
	virtual ~BufferObject() override;

	virtual void Update()override;
	void View(size_t size, size_t offset);
	void Write(void_ptr_cst data, size_t size, size_t offset);

	void Resize(size_t size);
	void Resize(size_t size, Usage usage);

	void SetUsage(Usage usage);
public:
	const BufferTarget target;
protected:
	byte_ptr _data;
	size_t _size;
	bool _is_reference;
	size_t _update_begin;
	size_t _update_size;
	Usage _usage;
};

NGS_END
NGL_END
