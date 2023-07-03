#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"

NGLGL_BEGIN

NGS_mfunction(layout, class _Element, class _Integral) {
	using element_type = _Element;
	constexpr static size_t count = _Integral::value;

	constexpr static auto tv_bitmap = gl_convert<element_type>;
	constexpr static size_t size = count * sizeof(element_type);

	NGS_mreturn_t element_type;
	NGS_mreturn count;
};

template<class _Element, size_t _Count>
using layout_c = layout<_Element, std::integral_constant<size_t, _Count>>;

NGS_mfunction(vertex, class _Unit, class... _Units) {
	NGS_mreturn_t boost::mpl::vector<_Unit, _Units...>;

	template<size_t _Index>
	using at = typename boost::mpl::at_c<type, _Index>::type;
	template<size_t _Index>
	using at_t = typename at<_Index>::type;
	template<size_t _Index>
	constexpr static size_t at_v = at<_Index>::value;

	constexpr static size_t count = 1 + sizeof...(_Units);
	constexpr static size_t size = (_Units::size + ... + _Unit::size);

	constexpr static std::array<size_t, count> counts = { _Unit::count,_Units::count... };
	constexpr static std::array<size_t, count> sizes = { _Unit::size,_Units::size... };
	constexpr static std::array<size_t, count> tv_bitmaps = { _Unit::tv_bitmap,_Units::tv_bitmap... };

	template<size_t _Index>
	constexpr static size_t offset = offset<_Index - 1> +at<_Index - 1>::size;
	template<>
	constexpr static size_t offset<0> = 0;

	constexpr static std::array<size_t, count> offsets = []<size_t... I>(std::index_sequence<I...>) {
		return std::array<size_t, count>{offset<I>...};
	}(std::make_index_sequence<count>{});
};

template<class _Element, size_t _L0, size_t... _LN>
using vertex_vector = vertex<layout_c<_Element, _L0>, layout_c<_Element, _LN>...>;

NGLGL_END
