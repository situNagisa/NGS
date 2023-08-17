#pragma once

#include "NGS/dl/defined.h"
#include "NGS/dl/display/bitmap/idata.h"
#include "NGS/dl/display/bitmap/data.h"

NGS_DL_BEGIN

class NGS_API  BitmapDataView final: public IBitmapData {
public:
	explicit(false) BitmapDataView(const BitmapData& other)
		: _data(other.GetData())
		, _format(other.GetFormat())
		, _width(other.GetWidth())
		, _height(other.GetHeight())
	{}

	BitmapDataView(const void_ptr_cst data, const color_space::PixelFormat format,const size_t width,const size_t height)
		: _data(static_cast<byte_ptr_cst>(data))
		, _format(format)
		, _width(width)
		, _height(height)
	{}
	virtual ~BitmapDataView() override = default;

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

NGS_DL_END
