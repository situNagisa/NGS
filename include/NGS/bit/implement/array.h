#pragma once

#include "../concept.h"
#include "../algorithm.h"
#include "../operator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<concepts::bit_operatable T, ::std::size_t BitSize>
	requires ::std::is_object_v<T> && ::std::copy_constructible<T>
struct array : operators::adl_forward<external::stl::ranges::range_interface<array<T, BitSize>>>
{
	NGS_PP_INJECT(array);
public:
	using value_type = T;
	constexpr static auto unit_size() { return algorithm::static_size<value_type>(); }
	constexpr static auto size() { return BitSize; }
	consteval static bool assignable() noexcept { return ::std::assignable_from<value_type&, value_type>; }

	consteval static auto _data_size() noexcept { return size() / unit_size() + static_cast<bool>(size() % unit_size()); }
	using data_type = ::std::array<value_type, _data_size()>;

	constexpr static auto _local_index(::std::size_t index) noexcept
	{
		if constexpr(::std::has_single_bit(unit_size()))
		{
			constexpr auto unit_shift = ::std::countr_zero(unit_size());
			return ::std::make_pair(index >> unit_shift, index & (unit_size() - 1));
		}
		else
		{
			return ::std::make_pair(index / unit_size(), index % unit_size());
		}
	}

	constexpr array() requires ::std::default_initializable<data_type> = default;
	constexpr explicit(false) array(auto&&... args) requires (::std::convertible_to<decltype(args), value_type> && ...) && (sizeof...(args) == _data_size())
		: _data{ NGS_PP_PERFECT_FORWARD(args)... }
	{}

	constexpr self_type& operator=(const self_type&) = default;
	//constexpr self_type& operator=(self_type&&) = default;

	constexpr self_type& operator=(const concepts::range auto& other)
	{
		::std::ranges::copy(other, begin());
		return *this;
	}

	constexpr self_type& operator&=(const self_type& other) noexcept requires (assignable())
	{
		for (auto&& [left, right] : ::std::views::zip(_data, other._data))
		{
			left = left & right;
		}
		return *this;
	}
	constexpr self_type& operator|=(const self_type& other) noexcept requires (assignable())
	{
		for (auto&& [left, right] : ::std::views::zip(_data, other._data))
		{
			left = left | right;
		}
		return *this;
	}
	constexpr self_type& operator^=(const self_type& other) noexcept requires (assignable())
	{
		for (auto&& [left, right] : ::std::views::zip(_data, other._data))
		{
			left = left ^ right;
		}
		return *this;
	}
private:
	template<class T>
	struct bit
	{
		using value_type = type_traits::object_t<T>*;

		consteval static bool assignable() noexcept { return ::std::assignable_from<type_traits::object_t<T>&, type_traits::object_t<T>>; }

		constexpr bit(value_type value, ::std::size_t index) : _value(value), _index(index) {}

		constexpr void set() const requires (assignable())
		{
			auto [index, offset] = _local_index(_index);
			algorithm::set((*_value)[index], offset);
		}
		constexpr void reset() const requires (assignable())
		{
			auto [index, offset] = _local_index(_index);
			algorithm::reset((*_value)[index], offset);
		}
		constexpr void flip() const requires (assignable())
		{
			auto [index, offset] = _local_index(_index);
			algorithm::flip((*_value)[index], offset);
		}
		constexpr bool test() const
		{
			auto [index, offset] = _local_index(_index);
			return algorithm::test((*_value)[index], offset);
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

	constexpr auto begin() const noexcept { return wrapper_iterator<const data_type>(_data, 0); }
	constexpr auto end() const noexcept { return wrapper_iterator<const data_type>(_data, sizeof(T) * size()); }

	constexpr auto begin() noexcept { return wrapper_iterator<data_type>(_data, 0); }
	constexpr auto end() noexcept { return wrapper_iterator<data_type>(_data, sizeof(T) * size()); }


	data_type _data{};
};

NGS_LIB_MODULE_END