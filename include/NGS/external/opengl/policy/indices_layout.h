#pragma once

#include "./layout.h"
#include "./indices.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<cpt::derived_from_specialization<layout> Layout, cpt::derived_from_specialization<indices_buffer> IndicesBuffer>
struct indices_layout
{
	NGS_PP_INJECT_BEGIN(indices_layout);
public:
	using layout_type = Layout;
	using indices_buffer_type = IndicesBuffer;
	using vertex_type = typename layout_type::vertex_type;

	indices_layout(layout_type&& layout, indices_buffer_type&& indices_buffer)
		: _layout(::std::move(layout))
		, _indices_buffer(::std::move(indices_buffer))
	{}

	decltype(auto) copy_vertex_range(
		::std::ranges::sized_range auto&& vertex_range, 
		buffer_value_t<indices_buffer_type> begin_index,
		::std::ranges::iterator_t<layout_type> vertex_out,
		::std::ranges::iterator_t<buffer_range_t<indices_buffer_type>> indices_out
	)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>, ::std::ranges::iterator_t<layout_type>>
	{
		auto indices_result = _indices_buffer.vertex_indices(begin_index, ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vertex_range)), indices_out);
		auto layout_result = ::std::ranges::copy(NGS_PP_PERFECT_FORWARD(vertex_range), vertex_out).out;

		return ::std::pair{ layout_result, indices_result };
	}

	decltype(auto) copy_vertex_range(
		::std::ranges::sized_range auto&& vertex_range,
		buffer_value_t<indices_buffer_type> begin_index,
		::std::ranges::range_difference_t<layout_type> vertex_out,
		::std::ranges::range_difference_t<buffer_range_t<indices_buffer_type>> indices_out
	)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>, ::std::ranges::iterator_t<layout_type>>
	{
		auto&&[layout,indices] = self_type::copy_vertex_range(NGS_PP_PERFECT_FORWARD(vertex_range), begin_index, vertex_out, indices_out);
		return ::std::pair{ ::std::ranges::distance(vertex_out, layout), ::std::ranges::distance(indices_out, indices) };
	}

	decltype(auto) copy_vertex_range(
		::std::initializer_list<vertex_type>&& vertex_range,
		buffer_value_t<indices_buffer_type> begin_index,
		::std::ranges::iterator_t<layout_type> vertex_out,
		::std::ranges::iterator_t<buffer_range_t<indices_buffer_type>> indices_out
	)
	{
		return self_type::copy_vertex_range(vertex_range, begin_index, vertex_out, indices_out);
	}
	decltype(auto) copy_vertex_range(
		::std::initializer_list<vertex_type>&& vertex_range,
		buffer_value_t<indices_buffer_type> begin_index,
		::std::ranges::range_difference_t<layout_type> vertex_out,
		::std::ranges::range_difference_t<buffer_range_t<indices_buffer_type>> indices_out
	)
	{
		return self_type::copy_vertex_range(vertex_range, begin_index, vertex_out, indices_out);
	}


	auto&& layout() { return _layout; }
	auto&& layout() const { return _layout; }

	auto&& indices_buffer() { return _indices_buffer; }
	auto&& indices_buffer() const { return _indices_buffer; }

	void describe(enums::usage vertex_usage, enums::usage indices_usage)
	{
		_layout.describe(vertex_usage);
		basic::bind(_indices_buffer.get_context());
		_indices_buffer.describe(indices_usage);
	}
	void describe(enums::usage usage)
	{
		self_type::describe(usage, usage);
	}

	void submit()
	{
		_layout.submit();
		basic::bind(_indices_buffer.get_context());
		_indices_buffer.submit();
	}

	void draw(::std::ranges::range_difference_t<buffer_range_t<indices_buffer_type>> offset, ::std::ranges::range_size_t<buffer_range_t<indices_buffer_type>> count)
	{
		NGS_ASSERT(static_cast<::std::ranges::range_difference_t<buffer_range_t<indices_buffer_type>>>(offset + count) <= ::std::ranges::size(_indices_buffer.data()), "out of range");
		algorithm::vertex_draw_elements(_layout.get_context(), typename indices_buffer_type::indices_drawer_type::draw_mode(), count, reflecter::reflect<buffer_value_t<indices_buffer_type>>::value.value, offset);
	}
	void draw() { self_type::draw(0, ::std::ranges::size(_indices_buffer.data())); }

	layout_type _layout;
	indices_buffer_type _indices_buffer;
};

NGS_LIB_MODULE_END