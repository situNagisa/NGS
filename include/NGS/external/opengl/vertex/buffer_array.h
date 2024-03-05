#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./array.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

template<vertex_buffer... Buffers>
struct buffer_array
{
	NGS_MPL_ENVIRON_BEGIN(buffer_array);
public:
	using buffers_type = ::std::tuple<Buffers...>;
public:
	buffer_array(cpt::naked_same_as<buffers_type> auto&& buffers) requires ::std::constructible_from<buffers_type,decltype(buffers)>
		: _buffers(NGS_PP_PERFECT_FORWARD(buffers))
	{}
	explicit buffer_array(vertex_buffer auto&&... buffers) requires ::std::constructible_from<buffers_type,decltype(::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))>
		: self_type(::std::make_tuple(NGS_PP_PERFECT_FORWARD(buffers)...))
	{}
	buffer_array() requires (sizeof...(Buffers) != 0) && ::std::constructible_from<buffers_type>
		: self_type(buffers_type{})
	{}

	constexpr auto&& data() { return _buffers; }
	constexpr auto&& data()const { return _buffers; }
private:
	buffers_type _buffers{};
};

NGS_LIB_MODULE_END