#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
template<class...>
struct tuple
{
	NGS_MPL_ENVIRON_BEGIN(tuple);
public:
	using sequence_type = self_type;
	constexpr static size_t sequence_size = 0;
};

template<class _First, class... _Rest>
struct tuple<_First, _Rest...> : tuple<_Rest...>
{
	NGS_MPL_ENVIRON(tuple);
public:
	using sequence_type = self_type;
	constexpr static size_t sequence_size = sizeof...(_Rest) + 1;

	constexpr tuple() = default;
	constexpr tuple(auto&& first, auto&&... rest)
		: base_type(NGS_PP_PERFECT_FORWARD(rest)...)
		, _value(NGS_PP_PERFECT_FORWARD(first))
	{}

	constexpr auto&& base() { return static_cast<base_type&>(*this); }
	constexpr auto&& base() const { return static_cast<const base_type&>(*this); }

	constexpr auto&& value() { return _value; }
	constexpr auto&& value()const { return _value; }

public:
	//this `public` is for `structured type`
	_First _value;
};


#if defined(__cpp_deduction_guides)
template<class... _Args>
tuple(_Args&&...) -> tuple<_Args...>;
#endif

NGS_LIB_MODULE_END