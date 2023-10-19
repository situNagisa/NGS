#pragma once

#include "./concept.h"
#include "./dynamic_data.h"

NGS_NGL_FUSION_BEGIN

template<CFundamental _ElementType>
constexpr auto make_attrib(size_t element_count, size_t offset = 0, bool normalize = false) {
	using element_type = _ElementType;

	attrib_dynamic_data data{};

	data.count = element_count;
	data.size = element_count * sizeof(element_type);
	data.offset = offset;
	data.type = gl_convert<element_type>;
	data.normalized = normalize;

	return data;
}

template<CFundamental _ElementType, size_t _Count>
constexpr auto make_attrib() {
	return make_attrib<_ElementType>(_Count);
}

template<CAttrib _Attrib>
constexpr auto make_attrib() {
	return make_attrib<typename _Attrib::element_type, _Attrib::element_count>();
}

NGS_NGL_FUSION_END
