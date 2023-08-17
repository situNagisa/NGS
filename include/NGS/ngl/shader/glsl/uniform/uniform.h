#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

using uniform_offset_t = GLint;

template<size_t _Size, class  _ElementType>
struct NGS_API basic_static_string {
	using element_type = _ElementType;
	constexpr static size_t size = _Size;

	constexpr basic_static_string(const element_type(&str)[size])
		: data(str) {}

	element_type data[size];
};

template<size_t _Size>
using static_string = basic_static_string<_Size, char>;

template<size_t _N, basic_static_string<_N, char> _Name, class  _Type>
struct NGS_API Uniform {
	using type = _Type;
	constexpr static auto name = _Name;

	uniform_offset_t location = 0;
};


NGL_END
