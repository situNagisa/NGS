#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class ValueType,class InnerType>
struct basic_bit_pointer
{
	NGS_PP_INJECT_BEGIN(basic_bit_pointer);
public:
	using value_type = ValueType;
	using value_pointer_type = ::std::add_pointer_t<value_type>;
	using inner_type = InnerType;

	constexpr static bool valid_pointer() noexcept
	{
		return sizeof(value_pointer_type) == sizeof(InnerType);
	}

	using pointer_type = ::std::conditional_t<valid_pointer(), value_pointer_type,inner_type>;

	constexpr basic_bit_pointer() noexcept = default;
	constexpr explicit(false) basic_bit_pointer(value_pointer_type value) noexcept
		: _value(reinterpret_cast<pointer_type>(value))
	{}
	constexpr explicit(false) basic_bit_pointer(inner_type value) noexcept
		: _value(reinterpret_cast<pointer_type>(value))
	{}

	constexpr auto pointer() const noexcept
	{
		if constexpr (valid_pointer())
		{
			return _value;
		}
		else
		{
			return reinterpret_cast<value_pointer_type>(_value);
		}
	}

	constexpr explicit(false) operator value_pointer_type() const noexcept { return pointer(); }

	constexpr decltype(auto) operator()(auto&&... args)const
		requires ::std::invocable<value_pointer_type,decltype(args)...>
	{
		return (pointer())(NGS_PP_PERFECT_FORWARD(args)...);
	}

	constexpr decltype(auto) value() const
	{
		if constexpr (valid_pointer())
		{
			return reinterpret_cast<inner_type>(_value);
		}
		else
		{
			return _value;
		}
	}

	pointer_type _value{};
};

template<class T = void>
using pointer_32 = basic_bit_pointer<T, ::std::uint32_t>;

template<class T = void>
using pointer_64 = basic_bit_pointer<T, ::std::uint64_t>;

NGS_LIB_END