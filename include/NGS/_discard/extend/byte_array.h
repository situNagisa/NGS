#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

class NGS_DLL_API  ByteArray {
public:

public:
	template<typename T>
		requires std::ranges::bidirectional_range<T>&& std::ranges::sized_range<T>&& std::convertible_to<std::ranges::range_value_t<T>, byte>
	void Bind(const T& range) {
		_data.resize(std::ranges::size(range));
		std::ranges::copy(range, std::ranges::begin(_data));
	}
	template<typename T>
		requires std::ranges::bidirectional_range<T>&& std::ranges::sized_range<T>&& std::convertible_to<std::ranges::range_value_t<T>, byte>
	void Write(const T& range) {
		_data.reserve(std::size(range));

		if constexpr (std::endian::native == std::endian::big) {
			_data.insert(_data.end(), std::ranges::rbegin(range), std::ranges::rend(range));
		}
		else {
			_data.insert(_data.end(), std::ranges::begin(range), std::ranges::end(range));
		}
	}
	template<typename T>
		requires (!std::ranges::range<T>)
	void Write(T&& obj) {
		std::array<byte, sizeof(T)> binary;
		std::memcpy(binary.data(), &obj, binary.size());
		Write<decltype(binary)>(binary);
	}
	template<typename T>
		requires std::ranges::bidirectional_range<T>&& std::ranges::sized_range<T>&& std::ranges::output_range<T, byte>&& std::convertible_to<std::ranges::range_value_t<T>, byte>
	void Read(T&& range) {
		if constexpr (std::endian::native == std::endian::big) {
			std::ranges::copy(_data | std::views::drop(_position) | std::views::take(std::ranges::size(range)), std::rbegin(range));
		}
		else {
			std::ranges::copy(_data | std::views::drop(_position) | std::views::take(std::ranges::size(range)), std::begin(range));
		}
		_position += std::ranges::size(range);
	}
	template<typename T>
	void Read(T&& obj) {
		std::array<byte, sizeof(T)> binary;
		Read<decltype(binary)>(binary);
		std::memcpy(&obj, binary.data(), binary.size());
	}
	template<typename T>
	T Read() {
		std::array<byte, sizeof(T)> binary{};
		Read(binary);
		return *reinterpret_cast<T*>(binary.data());
	}

	byte_ptr_cst Data()const { return _data.data(); }
	const std::vector<byte>& Container()const { return _data; }

	void Clear() {
		_data.clear();
		_position = 0;
	}
	size_t Size()const { return _data.size(); }
	size_t Position()const { return _position; }
	void SetPosition(size_t pos) { _position = pos; }
	void MovePosition(int off) { _position += off; }
private:

private:
	size_t _position = 0;
	std::vector<byte> _data = {};
};

NGS_END
