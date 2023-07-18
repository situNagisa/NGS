#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/gl_enum.h"

NGL_BEGIN

using indices_t = uint32;

NGL_BUF_BEGIN

class Indices : public BufferObject {
public:
	Indices(void_ptr data, size_t count, Usage usage);
	Indices(size_t count, Usage usage);
	Indices(Indices&&) = default;
	~Indices() = default;

	const indices_t* GetData()const { return std::launder(reinterpret_cast<const indices_t*>(_data)); }

	void View(size_t count, size_t offset);
	void Write(const indices_t* data, size_t count, size_t offset);

	constexpr static type_t type = gl_convert<indices_t>;
	constexpr static size_t format_size = sizeof(indices_t);
};

NGS_END
NGL_END
