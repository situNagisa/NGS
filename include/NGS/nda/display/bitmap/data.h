#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/bitmap/idata.h"

NDA_BEGIN

class NGS_API  BitmapData : public IBitmapData {
public:
	BitmapData(void_ptr data, color_space::PixelFormat format, size_t width, size_t height)
		: _data(reinterpret_cast<byte_ptr>(data), width* height* format.size)
		, _format(format)
		, _width(width)
		, _height(height)
	{}
	//copy
	BitmapData(const BitmapData& other)
		: _data()
		, _format(other._format)
		, _width(other._width)
		, _height(other._height)
	{
		auto size = _width * _height * _format.size;
		_data = std::span<byte>(new byte[size], size);
		std::ranges::copy(other._data, _data.begin());
	}
	BitmapData& operator=(const BitmapData& other) {
		delete _data.data();

		_format = other._format;
		_width = other._width;
		_height = other._height;

		auto size = _width * _height * _format.size;
		_data = std::span<byte>(new byte[size], size);
		std::ranges::copy(other._data, _data.begin());
	}
	//move
	BitmapData(BitmapData&& other)
		: _data(std::move(other._data))
		, _format(other._format)
		, _width(other._width)
		, _height(other._height)
	{
		other._width = other._height = 0;
	}
	BitmapData& operator=(BitmapData&& other) {
		delete _data.data();

		_data = std::move(other._data);
		_format = other._format;
		_width = other._width;
		_height = other._height;

		other._width = other._height = 0;
	}

	virtual ~BitmapData() {
		if (_width * _height)
			delete _data.data();
	}

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

NDA_END
