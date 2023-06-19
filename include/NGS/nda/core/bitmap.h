#pragma once
#include "NGS/nda/defined.h"
#include "NGS/nda/core/display_object.h"

NDA_BEGIN

class BitmapData {
public:
	NGS_TYPE_DEFINE(BitmapData, this);

public:
	BitmapData(size_t width, size_t height)
		: _size({ width,height })
		, _data(NGS_NEW_ARRAY(__color, width* height))
	{}
	BitmapData(size_t width, size_t height, __color_ptr_cst data)
		: BitmapData(width, height)
	{
		_CopyData(data);
	}
	BitmapData(__this_ref_cst other)
		: BitmapData(other.Width(), other.Height(), other._data)
	{}
	BitmapData(__this_right other)
		: _size(other._size)
		, _data(other._data)
	{
		other._data = nullptr;
	}
	~BitmapData() {
		if (_data)
			ngs::Delete(_data);
	}

	__this_ref operator=(__this_ref_cst other) {
		if (_size != other._size)
			_Resize(other._size);
		_CopyData(other._data);
		return *this;
	}
	__this_ref operator=(__this_right other) {
		_size = other._size;
		_data = other._data;
		other._data = nullptr;
	}
	__color_ptr Data() { return _data; }
	__color_ptr_cst Data()const { return _data; }

	size_t Width()const { return _size.x; }
	size_t Height()const { return _size.y; }

	size_t Size()const { return sizeof(__color) * _size.x * _size.y; }
private:
	void _Release() {
		ngs::Delete(_data);
	}
	void _Resize(const Point2s& size) {
		_Release();
		_size = size;
		_data = NGS_NEW_ARRAY(__color, _size.x * _size.y);
	}
	void _CopyData(__color_ptr_cst data) {
		std::memcpy(_data, data, Size());
	}
private:
	Point2s _size = {};
	__color_ptr _data = nullptr;
};

class BitmapDataView {
public:
	NGS_TYPE_DEFINE(BitmapDataView, this);

public:
	BitmapDataView(size_t width, size_t height, __color_ptr data)
		: _size(width, height)
		, _data(data)
	{}
	BitmapDataView(const BitmapData& bitmap_data)
		: _size(bitmap_data.Width(), bitmap_data.Height())
		, _data(bitmap_data.Data())
	{}
	~BitmapDataView() {
		_size.SetZero();
		_data = nullptr;
	}
	__color_ptr_cst Data()const { return _data; }

	size_t Width()const { return _size.x; }
	size_t Height()const { return _size.y; }

	size_t Size()const { return sizeof(__color) * _size.x * _size.y; }
private:
	Point2s _size = {};
	__color_ptr_cst _data = nullptr;

};

class Bitmap : public DisplayObject {
public:
	NGS_TYPE_DEFINE(BitmapData, data);

public:
	using DisplayObject::DisplayObject;
	Bitmap(__data_ref data)
		: _data(&data)
	{}

	__data_ptr Data() { return _data; }
	__data_ptr_cst Data()const { return _data; }

	__number Width()const override { return _data->Width() * ScaleX(); }
	__number Height()const override { return _data->Height() * ScaleY(); }

private:

private:
	__data_ptr _data;
};

NDA_END
