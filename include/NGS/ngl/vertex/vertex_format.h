#pragma once

#include "NGS/ngl/defined.h"

/**
 *											buffer0					buffer1		 buf2   buf3	...
 *												⬇						⬇		   ⬇		 ⬇		...
 *					|				-----------------------------------------------------------------------
 *					|	vertex0 ->	| attrib0,attrib1,attrib2 | attrib3,attrib4 | ... | ... |	...
 *					|				----------------------------------------------------------------------
 *					|				-----------------------------------------------------------------------
 *	vertex array  ⬅	|	vertex1 ->	| attrib0,attrib1,attrib2 | attrib3,attrib4 | ... | ... |	...
 *					|				----------------------------------------------------------------------
 *					|		.
 *					|		.
 *					|		.
 *
 *										array
 *										  ⬇
 *		-------------------------------------------------------------------------
 *		|	vertex	|	vertex	|	vertex	|	vertex	|	vertex	|	vertex	|
 *		-------------------------------------------------------------------------
 *										vertex
 *										  ⬇
 *		-------------------------------------------------------------------------
 *		|	buffer	|	buffer	|	buffer	|	buffer	|	buffer	|	buffer	|
 *		-------------------------------------------------------------------------
 *										buffer
 *										  ⬇
 *		-------------------------------------------------------------------------
 *		|	attrib	|	attrib	|	attrib	|	attrib	|	attrib	|	attrib	|
 *		-------------------------------------------------------------------------
 *
 */

NGL_BEGIN

struct NGS_API Attrib {
	type_t type;
	size_t count;
	size_t size;
	size_t offset;

	bool normalized;
};

template<CFundamental T, size_t _Count = 1>
using attrib_ = mpl::var_<T, _Count>;

NGS_mfunction(buffer, CFundamental T, ccpt::UInt... _Size) : mpl::meta_struct_c<attrib_<T, _Size::value>...>{
	NGS_mcst_t base = mpl::meta_struct_c<attrib_<T, _Size::value>...>;

	NGS_mcst_t element_type = T;
	NGS_mcst size_t element_count = (... + _Size::value);

	NGS_mcst_t view = std::span<element_type>;

	using type = std::array<element_type, element_count>;
};

template<CFundamental T, size_t... _Size>
using buffer_c = buffer<T, ccpt::uint_<_Size>...>;

NGL_END

NGS_BEGIN
NGS_CONCEPT

template<class _Buffer>
concept CBuffer = requires() {
	typename _Buffer::element_type;
	typename _Buffer::view;
	typename _Buffer::type;
	{ _Buffer::element_count } -> std::convertible_to<size_t>;
		requires mpl::CMetaStruct<_Buffer>;
};

NGS_END
NGS_END

NGL_BEGIN

struct NGS_API Buffer {
	size_t count;
	size_t size;
	std::vector<Attrib> properties;
};


NGL_FAC_BEGIN

template<mpl::CVariable _Var>
Attrib _make_attrib() {
	Attrib property{};
	property.type = gl_convert<typename _Var::element_type>;
	property.count = _Var::element_count;
	property.size = _Var::size;
	property.offset = 0;
	property.normalized = false;
	return property;
}

template<CBuffer _Buffer>
Buffer make_buffer() {
	Buffer format{};
	format.count = _Buffer::count;
	format.size = _Buffer::size;
	[&format] <size_t... _I>(std::index_sequence<_I...>) {
		(format.properties.push_back(_make_attrib<typename _Buffer::template variable_at<_I>>()), ...);
	}(std::make_index_sequence<_Buffer::count>{});
	for (size_t i = 0; i < _Buffer::count; i++)
	{
		auto& prop = format.properties[i];
		prop.offset = _Buffer::variables[i].offset;
	}
	return format;
}

NGS_END
NGL_END
