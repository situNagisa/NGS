#pragma once

#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup>
struct auto_manager
{
	NGS_PP_INJECT_BEGIN(auto_manager);
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

	void draw(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::draw_mode mode, ::std::ranges::range_difference_t<group_type> offset, ::std::ranges::range_size_t<group_type> count)
	{
		NGS_ASSERT((offset + count) <= static_cast<::std::ranges::range_difference_t<group_type>>(::std::ranges::size(_group)), "out of range");
		_array.get_context().draw_array(mode, count, offset);
	}
	void draw(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::draw_mode mode) { self_type::draw(mode, 0, ::std::ranges::size(_group)); }

	group_type _group;
	NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_array _array;
};

template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup>
auto_manager(VertexGroup&&)->auto_manager<VertexGroup>;

template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup>
auto_manager(VertexGroup&&,bool) -> auto_manager<VertexGroup>;

NGS_LIB_MODULE_END