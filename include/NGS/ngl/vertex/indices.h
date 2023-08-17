#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/gl_enum.h"

NGL_BEGIN

using indices_t = uint32;

NGL_BUF_BEGIN

class NGS_API  Indices : public BufferObject {
public:
	Indices(void_ptr data, size_t count, Usage usage);
	Indices(size_t count, Usage usage);
	Indices(Indices&&) = default;
	~Indices() = default;

	const indices_t* GetData()const { return std::launder(reinterpret_cast<const indices_t*>(_data)); }

	void View(size_t count, size_t offset);
	void Write(const indices_t* data, size_t count, size_t offset);

	template<class  _Rng>
		requires std::ranges::random_access_range<_Rng>&& std::convertible_to<std::ranges::range_value_t<_Rng>, indices_t>
	void AddIndices(size_t offset, _Rng&& rng) {
		Write(std::ranges::cdata(rng), std::ranges::size(rng), offset);
	}

	size_t GetCapacity()const {
		NGS_ASSERT(_size % format_size == 0);
		return _size / format_size;
	}

	constexpr static type_t type = gl_convert<indices_t>;
	constexpr static size_t format_size = sizeof(indices_t);
};

NGS_END
NGL_END
