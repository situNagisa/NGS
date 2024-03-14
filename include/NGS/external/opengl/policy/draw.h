#pragma once

#include "../basic.h"
#include "../indices.h"
#include "../reflect.h"
#include "../algorithm.h"
#include "./shader.h"
#include "./layout.h"
#include "./indices.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class IndicesDrawer, cpt::derived_from_specialization<indices_buffer> IndicesBuffer>
	requires indices::indices_drawer<IndicesDrawer, buffer_value_t<IndicesBuffer>, ::std::ranges::iterator_t<buffer_range_t<IndicesBuffer>>>
void draw_element(
	const shader& shader, 
	const cpt::derived_from_specialization<layout> auto& layout,
	const IndicesBuffer& indices_buffer,
	::std::ranges::range_difference_t<buffer_range_t<IndicesBuffer>> offset,
	::std::ranges::range_size_t<buffer_range_t<IndicesBuffer>> count
	)
{
	basic::bind(shader.get_context());
	basic::bind(layout.get_context());
	basic::bind(indices_buffer.get_context());
	algorithm::vertex_draw_elements(layout.get_context(), IndicesDrawer::draw_mode(), count, reflecter::reflect<buffer_value_t<IndicesBuffer>>::value.value, offset);
}

NGS_LIB_MODULE_END