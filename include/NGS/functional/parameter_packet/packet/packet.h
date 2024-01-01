#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using statics::tuples::element;
using statics::tuples::element_t;
using statics::tuples::size;
using statics::tuples::size_v;


template<class... _Args>
struct packet : statics::tuples::tuple<type_traits::storage_t<_Args>...>
{
	NGS_MPL_ENVIRON2(packet, statics::tuples::tuple<type_traits::storage_t<_Args>...>);
public:
	using parameters_type = statics::tuples::tuple<_Args...>;

	constexpr packet(auto&&... args)
		: base_type(type_traits::store<_Args>(NGS_PP_PERFECT_FORWARD(args))...)
	{}
	using base_type::operator=;
};

template<class... _Args>
packet(_Args...) -> packet<_Args...>;

NGS_LIB_MODULE_END