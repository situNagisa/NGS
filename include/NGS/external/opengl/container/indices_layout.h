#pragma once

#include "../algorithm.h"
#include "../policy.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<policy::layout> Layout,cpt::derived_from_specialization<policy::indices_buffer> IndicesBuffer>
struct indices_layout
{
	NGS_MPL_ENVIRON_BEGIN(indices_layout);
public:
	using layout_type = Layout;
	using indices_buffer_type = IndicesBuffer;
	using vertex_type = typename layout_type::vertex_type;

	indices_layout(layout_type&& layout, indices_buffer_type&& indices_buffer)
		: _layout(::std::move(layout))
		, _indices_buffer(::std::move(indices_buffer))
	{}

	decltype(auto) push_back_vertex_range(::std::ranges::sized_range auto&& vertex_range)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>,::std::ranges::iterator_t<layout_type>>
	{
		using layout_iterator_type = ::std::ranges::iterator_t<layout_type>;
		using indices_iterator_type = ::std::ranges::iterator_t<policy::buffer_range_t<indices_buffer_type>>;
		::std::ranges::in_out_result<layout_iterator_type, layout_iterator_type> layout_result{};
		::std::ranges::in_out_result<indices_iterator_type, indices_iterator_type> indices_result{};

		indices_result.in = ::std::ranges::next(::std::ranges::begin(_indices_buffer.data()), _current_indices_index);
		indices_result.out = _indices_buffer.vertex_indices(static_cast<policy::buffer_value_t<indices_buffer_type>>(_current_layout_index), ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vertex_range)), indices_result.in);
		_current_indices_index += ::std::ranges::distance(indices_result.in, indices_result.out);

		layout_result.in = ::std::ranges::next(::std::ranges::begin(_layout), _current_layout_index);
		layout_result.out = ::std::ranges::copy(NGS_PP_PERFECT_FORWARD(vertex_range), layout_result.in).out;
		_current_layout_index += ::std::ranges::distance(layout_result.in, layout_result.out);

		return ::std::pair{ layout_result, indices_result };
	}

	decltype(auto) push_back_vertex_range(::std::initializer_list<vertex_type>&& vertex_range)
	{
		return self_type::push_back_vertex_range(vertex_range);
	}

	auto&& layout() { return _layout; }
	auto&& layout() const { return _layout; }

	auto&& vertex_size()const { return _current_layout_index; }

	auto&& indices_buffer() { return _indices_buffer; }
	auto&& indices_buffer() const { return _indices_buffer; }

	auto&& indices_size() const { return _current_indices_index; }

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

	void draw(::std::ranges::range_difference_t<policy::buffer_range_t<indices_buffer_type>> offset, ::std::ranges::range_size_t<policy::buffer_range_t<indices_buffer_type>> count)
	{
		NGS_ASSERT(static_cast<::std::ranges::range_difference_t<policy::buffer_range_t<indices_buffer_type>>>(offset + count) <= indices_size(), "out of range");
		algorithm::vertex_draw_elements(_layout.get_context(), typename indices_buffer_type::indices_drawer_type::draw_mode(), count, reflecter::reflect<policy::buffer_value_t<indices_buffer_type>>::value.value, offset);
	}
	void draw() { self_type::draw(0, indices_size()); }

	layout_type _layout;
	::std::ranges::range_difference_t<layout_type> _current_layout_index = 0;
	indices_buffer_type _indices_buffer;
	::std::ranges::range_difference_t<policy::buffer_range_t<indices_buffer_type>> _current_indices_index = 0;
};


NGS_LIB_MODULE_END
