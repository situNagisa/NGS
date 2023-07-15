#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

struct VertexProperty {
	type_t type;
	size_t count;
	size_t size;
	size_t offset;

	bool normalized;
};

template<CFundamental T, size_t _Count = 1>
using prop_ = mpl::var_<T, _Count>;

template<CTemplateFrom<mpl::member_var>... _Var>
using vertex_ = mpl::spread_struct_t<mpl::meta_struct_c<_Var...>>;
template<CFundamental T, size_t... _Size>
using vertex_c = vertex_<prop_<T, _Size>...>;

NGS_mfunction(vertex_array_, CTemplateFrom<mpl::meta_struct>... _Struct);

struct VertexFormat {
	size_t count;
	size_t size;
	std::vector<VertexProperty> properties;
};


NGL_FAC_BEGIN

template<CTemplateFrom<mpl::member_var> _Var>
VertexProperty _make_vertex_property() {
	VertexProperty property{};
	property.type = gl_convert<typename _Var::element_type>;
	property.count = _Var::count;
	property.size = _Var::size;
	property.offset = 0;
	property.normalized = false;
	return property;
}

template<CTemplateFrom<mpl::meta_struct> _Struct>
VertexFormat make_vertex_format() {
	VertexFormat format{};
	format.count = _Struct::count;
	format.size = _Struct::size;
	[&format] <size_t... _I>(std::index_sequence<_I...>) {
		(format.properties.push_back(_make_vertex_property<typename _Struct::template var_at<_I>>())...);
	}(std::make_index_sequence<_Struct::count>{});
	return format;
}

NGS_END

NGL_END
