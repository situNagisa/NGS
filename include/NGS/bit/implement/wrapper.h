#pragma once

#include "../concept.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<concepts::bit_operatable T>
struct wrapper : ::std::ranges::view_interface<wrapper<T>>
{
	NGS_PP_INJECT_EXPLICIT(wrapper, ::std::ranges::view_interface<wrapper>);
public:
	constexpr wrapper() noexcept = default;
	constexpr explicit(false) wrapper(auto&& value) noexcept requires ::std::constructible_from<T, decltype(value)>
		: _value(NGS_PP_PERFECT_FORWARD(value))
	{}
	constexpr wrapper(const self_type& other) : _value(other._value) {}

	constexpr auto&& value() noexcept { return _value; }
	constexpr auto&& value() const noexcept { return _value; }

	constexpr decltype(auto) operator&(const self_type& other) const noexcept { return self_type(_value & other._value); }
	constexpr decltype(auto) operator|(const self_type& other) const noexcept { return self_type(_value | other._value); }
	constexpr decltype(auto) operator^(const self_type& other) const noexcept { return self_type(_value ^ other._value); }
	constexpr decltype(auto) operator~() const noexcept { return self_type(~_value); }

	constexpr self_type& operator&=(const self_type& other) noexcept requires ::std::assignable_from<T,type_traits::object_t<T>> { _value = _value & other._value; return *this; }
	constexpr self_type& operator|=(const self_type& other) noexcept requires ::std::assignable_from<T,type_traits::object_t<T>> { _value = _value | other._value; return *this; }
	constexpr self_type& operator^=(const self_type& other) noexcept requires ::std::assignable_from<T,type_traits::object_t<T>> { _value = _value ^ other._value; return *this; }

	constexpr decltype(auto) operator<<(::std::integral auto shift) const noexcept { return self_type(_value << shift); }
	constexpr decltype(auto) operator>>(::std::integral auto shift) const noexcept { return self_type(_value >> shift); }

	constexpr self_type& operator<<=(::std::integral auto shift) noexcept requires ::std::assignable_from<T, type_traits::object_t<T>> { _value = (_value << shift); return *this; }
	constexpr self_type& operator>>=(::std::integral auto shift) noexcept requires ::std::assignable_from<T, type_traits::object_t<T>> { _value = (_value >> shift); return *this; }

private:
	template<class T>
	struct bit
	{
		using value_type = type_traits::object_t<T>*;

		consteval static bool assignable() noexcept { return ::std::assignable_from<type_traits::object_t<T>&, type_traits::object_t<T>>; }

		constexpr bit(value_type value, ::std::size_t index) : _value(value), _index(index) {}

		constexpr void set() const requires (assignable())
		{
			(*_value) = *_value | (1 << _index);
		}
		constexpr void reset() const requires (assignable())
		{
			(*_value) = *_value & ~(1 << _index);
		}
		constexpr void flip() const requires (assignable())
		{
			(*_value) = ~*_value;
		}
		constexpr bool test() const
		{
			return (*_value) & (1 << _index);
		}
		constexpr explicit(false) operator bool() const { return test(); }

		constexpr auto&& operator=(bool state) const requires (assignable())
		{
			state ? set() : reset();
			return *this;
		}
		constexpr auto&& operator=(const bit& other) const
		{
			this->operator=(other.test());
			return *this;
		}

		value_type _value;
		::std::size_t _index;
	};

	template<class T>
	struct wrapper_iterator : ::boost::stl_interfaces::iterator_interface<wrapper_iterator<T>, ::std::random_access_iterator_tag, bit<T>>
	{
		constexpr wrapper_iterator() noexcept = default;
		constexpr wrapper_iterator(type_traits::object_t<T>& value, ::std::size_t index) : _value(&value), _index(index) {}

		constexpr decltype(auto) operator*() const { return bit<T>(_value, _index); }
		constexpr decltype(auto) operator-(const wrapper_iterator& other) const { return static_cast<::std::ptrdiff_t>(_index - other._index); }
		constexpr auto&& operator+=(::std::ptrdiff_t offset) { _index += offset; return *this; }

		type_traits::object_t<T>* _value = nullptr;
		::std::size_t _index = 0;
	};

public:
	constexpr auto size() const noexcept
	{
		if constexpr (concepts::range<T>)
		{
			return ::std::ranges::size(_value);
		}
		else
		{
			return algorithm::bit_of<T>();
		}
	}

	constexpr auto begin() const noexcept { return wrapper_iterator<const type_traits::naked_t<T>>(_value, 0); }
	constexpr auto end() const noexcept { return wrapper_iterator<const type_traits::naked_t<T>>(_value, sizeof(T) * size()); }

	constexpr auto begin() noexcept { return wrapper_iterator<type_traits::naked_t<T>>(_value, 0); }
	constexpr auto end() noexcept { return wrapper_iterator<type_traits::naked_t<T>>(_value, sizeof(T) * size()); }

	T _value;
};

template<concepts::bit_operatable T>
wrapper(T) -> wrapper<T>;

NGS_LIB_MODULE_END