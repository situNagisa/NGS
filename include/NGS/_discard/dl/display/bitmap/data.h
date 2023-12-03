#pragma once

#include "NGS/dl/defined.h"
#include "NGS/dl/display/bitmap/idata.h"

NGS_DL_BEGIN

class NGS_DLL_API  BitmapData final : public IBitmapData {
public:
	BitmapData(const void_ptr data, const color_space::PixelFormat format, const size_t width, const size_t height);
	//copy
	BitmapData(const BitmapData& other);

	BitmapData& operator=(const BitmapData& other);

	//move
	BitmapData(BitmapData&& other) noexcept;

	BitmapData& operator=(BitmapData&& other) noexcept;

	virtual ~BitmapData() override;

	using IBitmapData::GetData;
	virtual byte_ptr GetData() { return _data.data(); }
	virtual byte_ptr_cst GetData()const override { return _data.data(); }
	virtual size_t GetSize()const { return _data.size(); }

	template<CColor _Color>
	_Color* GetData() { return std::launder(reinterpret_cast<_Color*>(GetData())); }

	virtual color_space::PixelFormat GetFormat()const override { return _format; }

	virtual size_t GetWidth()const override { return _width; }
	virtual size_t GetHeight()const override { return _height; }
private:
	std::span<byte> _data;
	PixelFormat _format;
	size_t _width;
	size_t _height;
};

NGS_DL_END
