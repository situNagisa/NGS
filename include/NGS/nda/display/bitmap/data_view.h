#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/bitmap/idata.h"
#include "NGS/nda/display/bitmap/data.h"

NDA_BEGIN

class NGS_DLL_API  BitmapDataView : public IBitmapData {
public:
	BitmapDataView(const BitmapData& other)
		: _data(other.GetData())
		, _format(other.GetFormat())
		, _width(other.GetWidth())
		, _height(other.GetHeight())
	{}

	BitmapDataView(void_ptr_cst data, color_space::PixelFormat format, size_t width, size_t height)
		: _data(reinterpret_cast<byte_ptr_cst>(data))
		, _format(format)
		, _width(width)
		, _height(height)
	{}
	virtual ~BitmapDataView() {}

	using IBitmapData::GetData;
	virtual byte_ptr_cst GetData()const override { return _data; }
	virtual size_t GetSize()const { return _width * _height * _format.size; }

	virtual color_space::PixelFormat GetFormat()const override { return _format; }

	virtual size_t GetWidth()const override { return _width; }
	virtual size_t GetHeight()const override { return _height; }

private:
	byte_ptr_cst _data;
	PixelFormat _format;
	size_t _width;
	size_t _height;
};

NDA_END
