#pragma once

#include "NGS/ngl/defined.h"


NGL_BEGIN

class ImageView {
private:

public:
	ImageView(void_ptr_cst data, size_t width, size_t height, type_t format)
		: _data(reinterpret_cast<byte_ptr_cst>(data))
		, _size(width, height)
		, _format(format)
	{}

	template<class T>
		requires (gl_convert<T> != 0)
	ImageView(const T* data, size_t width, size_t height)
		: ImageView(data, width, height, gl_convert<T>)
	{}

	auto GetData()const { return _data; }
	template<class T>
	const T* GetData()const { return std::launder(reinterpret_cast<const T*>(_data)); }

	const ngs::Point2s& GetSize()const { return _size; }

	type_t GetFormat()const { return _format; }
protected:
	byte_ptr_cst _data = nullptr;
	ngs::Point2s _size{};
	type_t _format{};
};

NGL_END
