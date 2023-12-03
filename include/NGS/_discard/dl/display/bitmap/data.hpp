#pragma once

#include "NGS/dl/display/bitmap/data.h"
#include "NGS/dl/graphic/api.h"

NGS_DL_BEGIN

NGS_HPP_INLINE BitmapData::BitmapData(const void_ptr data, const color_space::PixelFormat format, const size_t width, const size_t height)
	: _data(static_cast<byte_ptr>(data), width* height* format.size)
	, _format(format)
	, _width(width)
	, _height(height)
{
	GraphicAPI::I().listener.bitmap_data.constructor(this);
}

NGS_HPP_INLINE BitmapData::BitmapData(const BitmapData& other)
	: _data()
	, _format(other._format)
	, _width(other._width)
	, _height(other._height)
{
	const auto size = _width * _height * _format.size;
	_data = std::span<byte>(new byte[size], size);
	std::ranges::copy(other._data, _data.begin());

	GraphicAPI::I().listener.bitmap_data.constructor(this);
}

NGS_HPP_INLINE BitmapData& BitmapData::operator=(const BitmapData& other) {
	if (_width * _height) {
		delete _data.data();
		GraphicAPI::I().listener.bitmap_data.destructor(this);
	}

	_format = other._format;
	_width = other._width;
	_height = other._height;

	const auto size = _width * _height * _format.size;
	_data = std::span<byte>(new byte[size], size);
	std::ranges::copy(other._data, _data.begin());

	GraphicAPI::I().listener.bitmap_data.copy(this,&other);

	return *this;
}

NGS_HPP_INLINE BitmapData::BitmapData(BitmapData&& other) noexcept
	: _data(std::move(other._data))
	, _format(other._format)
	, _width(other._width)
	, _height(other._height)
{
	other._width = other._height = 0;
	GraphicAPI::I().listener.bitmap_data.move(this, &other);
}

NGS_HPP_INLINE BitmapData& BitmapData::operator=(BitmapData&& other) noexcept {
	if (_width * _height) {
		delete _data.data();
		GraphicAPI::I().listener.bitmap_data.destructor(this);
	}

	_data = std::move(other._data);
	_format = other._format;
	_width = other._width;
	_height = other._height;

	other._width = other._height = 0;

	GraphicAPI::I().listener.bitmap_data.move(this, &other);

	return *this;
}

NGS_HPP_INLINE BitmapData::~BitmapData() {
	if (_width * _height) {
		delete _data.data();
		GraphicAPI::I().listener.bitmap_data.destructor(this);
	}
}

NGS_DL_END
