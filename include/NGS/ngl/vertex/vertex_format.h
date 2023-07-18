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

struct Attrib {
	type_t type;
	size_t count;
	size_t size;
	size_t offset;

	bool normalized;
};

template<CFundamental T, size_t _Count = 1>
using attrib_ = mpl::var_<T, _Count>;

NGS_mfunction(buffer, CFundamental T, CIntegralConstant... _Size) : mpl::meta_struct_c<attrib_<T, _Size::value>...>{
	NGS_mcst_t base = mpl::meta_struct_c<attrib_<T, _Size::value>...>;

	NGS_mcst_t element_type = T;
	NGS_mcst size_t element_count = (... + _Size::value);

	NGS_mcst_t view = std::span<element_type>;

	NGS_mreturn_t std::array<element_type, element_count>;
};

template<CFundamental T, size_t... _Size>
using buffer_c = buffer<T, std::integral_constant<size_t, _Size>...>;

NGL_END

NGS_BEGIN
NGS_CONCEPT

template<class T>
concept CBuffer = CTemplateFrom<T, ngl::buffer>;

NGS_END
NGS_END

NGL_BEGIN

struct Buffer {
	size_t count;
	size_t size;
	std::vector<Attrib> properties;
};


NGL_FAC_BEGIN

template<CTemplateFrom<mpl::member_var> _Var>
Attrib _make_attrib() {
	Attrib property{};
	property.type = gl_convert<typename _Var::element_type>;
	property.count = _Var::count;
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
		(format.properties.push_back(_make_attrib<typename _Buffer::template var_at<_I>>()), ...);
	}(std::make_index_sequence<_Buffer::count>{});
	for (size_t i = 0; i < _Buffer::count; i++)
	{
		auto& prop = format.properties[i];
		prop.offset = _Buffer::vars[i].offset;
	}
	return format;
}

NGS_END
NGL_END
