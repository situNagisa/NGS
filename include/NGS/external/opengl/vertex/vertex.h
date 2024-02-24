#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./array.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

struct vertex_info
{
	bool normalized = false;
};

template<vertex_buffer... Buffers>
struct vertex
{
	NGS_MPL_ENVIRON_BEGIN(vertex);
public:
	using buffers_type = ::std::tuple<Buffers...>;
public:
	vertex(const vertex_info& info, cpt::naked_same_as<buffers_type> auto&& buffers) requires ::std::constructible_from<buffers_type,decltype(buffers)>
		: _buffers(NGS_PP_PERFECT_FORWARD(buffers))
	{
		NGS_LIB_MODULE_NAME::commit_layout(_array, info.normalized, _buffers);
	}
	explicit vertex(const vertex_info& info, vertex_buffer auto&&... buffers) requires ::std::constructible_from<buffers_type,decltype(::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))>
		: vertex(info, ::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))
	{}
	vertex(cpt::naked_same_as<buffers_type> auto&& buffers) requires ::std::constructible_from<buffers_type,decltype(buffers)>
		: vertex(vertex_info{}, NGS_PP_PERFECT_FORWARD(buffers))
	{}
	vertex(vertex_buffer auto&&... buffers) requires ::std::constructible_from<buffers_type,decltype(::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))>
		: vertex(::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))
	{}
	vertex() requires (sizeof...(Buffers) != 0) && ::std::constructible_from<buffers_type>
		: vertex(vertex_info{}, buffers_type{})
	{}



private:
	vertex_array _array{};
	buffers_type _buffers{};
};

NGS_LIB_MODULE_END