#pragma once

#include "NGS/ngl/defined.h"


NGL_BEGIN

class NGS_DLL_API  ImageView {
private:

public:
	ImageView(void_ptr_cst data, size_t width, size_t height, format_t format,internal_format_t internal_format,type_t type)
		: _data(static_cast<byte_ptr_cst>(data))
		, _size(width, height)
		, _format(format)
		, _internal_format(internal_format)
		, _type(type)
	{}

	ImageView(void_ptr_cst data, size_t width, size_t height, format_t format)
		: ImageView(data,width,height,format,static_cast<internal_format_t>(format),gl_convert<byte>)
	{}
	ImageView()
		: ImageView(nullptr,0,0,0)
	{}

	template<class  T>
		requires (gl_convert<T> != 0)
	ImageView(const T* data, size_t width, size_t height)
		: ImageView(data, width, height, gl_convert<T>)
	{}

	auto GetData()const { return _data; }
	template<class  T>
	const T* GetData()const { return std::launder(reinterpret_cast<const T*>(_data)); }

	const Point2s& GetSize()const { return _size; }

	format_t GetFormat()const { return _format; }
	internal_format_t GetInternalFormat()const { return _internal_format; }
	type_t GetType()const { return _type; }

	bool IsEmpty()const { return !(_size.x * _size.y); }
protected:
	byte_ptr_cst _data = nullptr;
	ngs::Point2s _size{};
	format_t _format{};
	internal_format_t _internal_format{};
	type_t _type{};
};

NGL_END
