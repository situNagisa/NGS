#pragma once

#include "../../../reflect.h"
#include "./auto.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<vertex_group> VertexGroup, cpt::derived_from_specialization<indices_buffer> IndexBuffer>
struct index_manager : auto_manager<VertexGroup>
{
	NGS_MPL_ENVIRON(index_manager);
public:
	using index_buffer_type = IndexBuffer;

	index_manager(typename base_type::group_type&& group, index_buffer_type&& index,bool normalized = false)
		: base_type(::std::move(group),normalized)
		, _index(::std::move(index))
	{}

	auto&& index_buffer() { return _index; }
	auto&& index_buffer() const { return _index; }

	void describe(enums::usage vertex_usage, enums::usage indices_usage)
	{
		base_type::group().describe(vertex_usage);
		contexts::bind(_index.get_context());
		_index.describe(indices_usage);
	}
	void describe(enums::usage usage)
	{
		self_type::describe(usage, usage);
	}

	void submit()
	{
		base_type::group().submit();
		contexts::bind(_index.get_context());
		_index.submit();
	}

	void draw(::std::ranges::range_difference_t<buffer_range_t<index_buffer_type>> offset, ::std::ranges::range_size_t<buffer_range_t<index_buffer_type>> count)
	{
		NGS_ASSERT(static_cast<::std::ranges::range_difference_t<buffer_range_t<index_buffer_type>>>(offset + count) <= ::std::ranges::size(_index.data()), "out of range");
		base_type::array().get_context().draw_elements(index_buffer_type::indexer_type::topology(), count, reflects::buffer_indices_reflecter::reflect<buffer_value_t<index_buffer_type>>::value.value, offset);
	}
	void draw() { self_type::draw(0, ::std::ranges::size(_index.data())); }

	index_buffer_type _index;
};

NGS_LIB_MODULE_END