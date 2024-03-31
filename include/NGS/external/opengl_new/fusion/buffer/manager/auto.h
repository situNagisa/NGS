#pragma once

#include "../vertex_array.h"
#include "../group.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<cpt::derived_from_specialization<vertex_group> VertexGroup>
struct auto_manager
{
	NGS_MPL_ENVIRON_BEGIN(auto_manager);
public:
	using group_type = VertexGroup;
	using vertex_type = typename group_type::vertex_type;

	explicit(false) auto_manager(group_type&& group, bool normalized = false)
		: _group(::std::move(group))
		, _array(_group, normalized)
	{}

	auto&& array() { return _array; }
	auto&& array() const { return _array; }

	auto&& group() { return _group; }
	auto&& group() const { return _group; }

	void draw(enums::draw_mode mode, ::std::ranges::range_difference_t<group_type> offset, ::std::ranges::range_size_t<group_type> count)
	{
		NGS_ASSERT(static_cast<::std::ranges::range_difference_t<group_type>>(offset + count) <= ::std::ranges::size(_group), "out of range");
		_array.get_context().draw_array(mode, count, offset);
	}
	void draw() { self_type::draw(0, ::std::ranges::size(::std::ranges::size(_group))); }

	group_type _group;
	vertex_array _array;
};

NGS_LIB_MODULE_END