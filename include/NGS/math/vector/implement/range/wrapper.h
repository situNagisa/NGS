#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

template<functor::accessible _Type>
struct value_wrapper
{
	using value_type = functor::value_t<_Type>;
	using range_type = _Type;

	constexpr value_wrapper(range_type* expression, size_t index) noexcept
		: _expression(expression), _index(index)
	{}

	constexpr decltype(auto) get()const noexcept
	{
		return functor::access(*_expression, _index);
	}
	constexpr decltype(auto) get() noexcept
	{
		return functor::access(*_expression, _index);
	}

	constexpr decltype(auto) operator=(auto&& value)
		requires functor::assignable<decltype(value), range_type>
	{
		return functor::assign(*_expression, _index, NGS_PP_PERFECT_FORWARD(value));
	}
	constexpr decltype(auto) operator=(auto&& value)const
		requires functor::assignable<decltype(value), range_type>
	{
		return functor::assign(*_expression, _index, NGS_PP_PERFECT_FORWARD(value));
	}

	constexpr operator decltype(auto) () noexcept{ return get(); }
	constexpr operator decltype(auto) () const noexcept{ return get(); }



private:
	range_type* _expression;
	size_t _index;
};

NGS_MATH_VECTOR_END