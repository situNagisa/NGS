#pragma once

#include "../reflect.h"
#include "../context.h"
#include "../indices.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::ranges::contiguous_range Range, indices::indices_drawer<::std::ranges::range_value_t<Range>,::std::ranges::iterator_t<Range>> IndicesDrawer>
	requires valid_fundamental<::std::ranges::range_value_t<Range>>
struct indices_buffer : buffer<contexts::indices_buffer, Range>
{
	NGS_MPL_ENVIRON2(indices_buffer, buffer<contexts::indices_buffer, Range>);
public:
	using indices_drawer_type = IndicesDrawer;

	using base_type::base_type;
	using base_type::operator=;

	constexpr auto vertex_indices(buffer_value_t<base_type> index,::std::size_t vertex_count, ::std::ranges::iterator_t<typename base_type::range_type> out)
	{
		return indices_drawer_type::vertex_indices(index, vertex_count, out);
	}
	constexpr decltype(auto) vertex_indices(buffer_value_t<base_type> index, ::std::size_t vertex_count, ::std::ranges::range_difference_t<typename base_type::range_type> offset)
	{
		return ::std::ranges::distance(self_type::vertex_indices(index, vertex_count, ::std::ranges::next(::std::ranges::begin(base_type::data()),offset)),::std::ranges::begin(base_type::data()));
	}
};



NGS_LIB_MODULE_END

