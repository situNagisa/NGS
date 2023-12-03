#pragma once

#include "NGS/extend/extend.h"

NGS_BEGIN

class NGS_DLL_API  Image {
public:

public:
	Image() : Image(nullptr, 0, 0, PixelFormat::unknown) {}
	Image(void_ptr_cst data, size_t width, size_t height, PixelFormat format)
		: _data((byte_ptr_cst)data)
		, width(width)
		, height(height)
		, format(format)
	{}
	~Image() {
		NGS_DELETE_ARR(_data);
	}

	Image(const Image& other)
		: _data(nullptr)
		, width(other.width)
		, height(other.height)
		, format(other.format)
	{
		//NGS_NEW_ARR
			//memcpy(_data, other._data, width * height * PixelFormatSize(format));
	}

public:
	const size_t width;
	const size_t height;
	const PixelFormat format;
private:
	byte_ptr_cst _data;

};

NGS_END
