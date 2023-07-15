#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

NGS_mfunction(layout, class _Element, class _Integral) {
	using element_type = _Element;
	constexpr static size_t element_count = _Integral::value;
	constexpr static size_t element_size = sizeof(element_type);

	constexpr static auto tv_bitmap = gl_convert<element_type>;
	constexpr static size_t size = element_count * element_size;

	NGS_mreturn_t element_type;
};

template<class _Element, size_t _Count>
using layout_c = layout<_Element, std::integral_constant<size_t, _Count>>;

struct Layout {
	constexpr Layout() = default;
	constexpr Layout(size_t offset, type_t type, size_t count, size_t size)
		: offset(offset)
		, type(type)
		, count(count)
		, size(size)
	{}
	constexpr Layout(size_t offset, type_t type, size_t count, size_t size, bool normalized, bool enable)
		: Layout(offset, type, count, size)
	{
		this->normalized = normalized;
		this->enable = enable;
	}

	size_t offset{};

	type_t type{};
	size_t count{};
	size_t size{};

	bool normalized = false;
	bool enable = true;
};
NGS_mfunction(vertex, class, class...);

NGS_mfunction(vertex, CTemplateFrom<layout> _Unit, CTemplateFrom<layout>... _Units) < _Unit, _Units... > {
	NGS_mreturn_t boost::mpl::vector<_Unit, _Units...>;

	template<size_t _Index>
	using layout_at_t = typename boost::mpl::at_c<type, _Index>::type;

	constexpr static size_t layout_count = 1 + sizeof...(_Units);
	constexpr static size_t size = (_Units::size + ... + _Unit::size);

	constexpr static std::array<size_t, layout_count> layout_counts = { _Unit::element_count,_Units::element_count... };
	constexpr static std::array<size_t, layout_count> layout_sizes = { _Unit::size,_Units::size... };
	constexpr static std::array<size_t, layout_count> layout_tv_bitmaps = { _Unit::tv_bitmap,_Units::tv_bitmap... };

	constexpr static size_t element_count = []<size_t... I>(std::index_sequence<I...>) {
		return (layout_at_t<I>::element_count + ...);
	}(std::make_index_sequence<layout_count>{});
private:
	template<size_t _Index> constexpr static size_t _layout_offset = _layout_offset<_Index - 1> +layout_sizes[_Index - 1];
	template<> constexpr static size_t _layout_offset<0> = 0;

public:
	constexpr static std::array<size_t, layout_count> layout_offsets = []<size_t... I>(std::index_sequence<I...>) {
		return std::array<size_t, layout_count>{_layout_offset<I>...};
	}(std::make_index_sequence<layout_count>{});

	constexpr static std::array<Layout, layout_count> layouts = []<size_t... I>(std::index_sequence<I...>) {
		return std::array<Layout, layout_count>{Layout{_layout_offset<I>, layout_tv_bitmaps[I], layout_counts[I], layout_sizes[I]}...};
	}(std::make_index_sequence<layout_count>{});
};

NGS_mfunction(vertex, CTemplateFrom<layout>... _Layouts) < vertex<_Layouts...> > : public vertex<_Layouts...>{};
NGS_mfunction(vertex, CTemplateFrom<layout>... _Layouts1, CTemplateFrom<layout>... _Layouts2) < vertex<_Layouts1...>, vertex<_Layouts2...> > : public vertex<_Layouts1..., _Layouts2...>{};

NGS_mfunction(vertex, CTemplateFrom<layout>... _Layouts1, CTemplateFrom<layout>... _Layouts2, CTemplateFrom<vertex>... _Vertex3)
< vertex<_Layouts1...>, vertex<_Layouts2...>, _Vertex3... >
	: public vertex<vertex<_Layouts1..., _Layouts2...>, _Vertex3...>{};

template<class _Element, size_t _L0, size_t... _LN>
using vertex_c = vertex<layout_c<_Element, _L0>, layout_c<_Element, _LN>...>;

struct Vertex {
public:
	using value_type = gl::Layout;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;

	constexpr Vertex(Usage usage, const_iterator begin, size_t count, size_t size)
		: usage(usage)
		, _begin(begin)
		, _count(count)
		, _size(size)
	{}
	constexpr Vertex(Usage usage, const std::ranges::random_access_range auto& layouts, size_t size)
		: Vertex(usage, &*std::ranges::cbegin(layouts), std::ranges::size(layouts), size)
	{}

	constexpr bool empty()const { return size(); }

	constexpr const_iterator begin() { return _begin; }
	constexpr const_iterator end() { return _begin + _count; }

	constexpr const_reference operator[](size_type n)const { return *(_begin + n); }

	const_reference at(size_type n) const {
		NGS_ASSERT(n < _count, "out of range");
		return *(_begin + n);
	}
	constexpr size_type size() const { return _count; }

	constexpr size_type step()const { return _size; }

	Usage usage;
private:
	const_iterator _begin;
	size_type _count;
	size_type _size;
};
static_assert(std::ranges::random_access_range<Vertex>);

template<CTemplateFrom<vertex> _Vertex>
struct CreateVertex : Vertex {
	using Vertex::Vertex;
	constexpr CreateVertex(Usage usage)
		: Vertex(usage, _Vertex::layouts.data(), _Vertex::layouts.size(), _Vertex::size)
	{}
};


NGLGL_END
