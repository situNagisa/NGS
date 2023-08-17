#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/texture/texture.h"

NGL_BEGIN

template<std::derived_from<objects::_Texture> _TextureType>
class NGS_API  TexturePool : DeleteCopy {
public:
	using texture_type = _TextureType;
public:
	TexturePool(size_t n)
		: _data(n)
	{}
	TexturePool(TexturePool&& other)
		: _data(std::move(other._data))
		, _count(other._count)
	{
		other._data.clear();
		other._count = 0;
	}

	auto GetSpan() {
		return std::span<texture_type>(_data.data(), _count);
	}
	auto& AddTexture(const ImageView& image, size_t mipmap = 0) {
		NGS_ASSERT(_count < _data.size());
		auto& texture = _data[_count];
		texture.SetImage(image, mipmap);
		_count++;

		return texture;
	}
	bool IsFull()const { return _count == _data.size(); }
	void Clear() {
		_count = 0;
	}

private:
	std::vector<texture_type> _data{};
	size_t _count = 0;
};

NGL_END
