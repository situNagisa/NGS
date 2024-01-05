#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_RANGE_BEGIN
namespace detail {

	template<concepts::vectors::accessible _Accessor, class _ValueType>
	struct vector_iterator_impl
	{
	protected:
		using self_type = vector_iterator_impl;
	public:
		using value_type = _ValueType;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		using accessor_type = _Accessor;

		constexpr vector_iterator_impl() noexcept = default;
		constexpr vector_iterator_impl(accessor_type* vector, difference_type index) noexcept
			: _accessor(vector), _index(index) {}

		constexpr vector_iterator_impl(const self_type&)noexcept = default;
		constexpr vector_iterator_impl(self_type&&) noexcept = default;
		constexpr self_type& operator=(const self_type&) noexcept = default;
		constexpr self_type& operator=(self_type&&) noexcept = default;

		constexpr decltype(auto) operator*()const { return adapters::vectors::access(*_accessor, _index); }
		constexpr decltype(auto) operator-(const self_type& other)const { return _index - other._index; }
		constexpr decltype(auto) operator+=(difference_type offset) { _index += offset; return *this; }
		constexpr decltype(auto) operator-=(difference_type offset) noexcept { return operator+=(-offset); }

		constexpr self_type operator+(difference_type offset) const noexcept { return self_type(_accessor, _index + offset); }
		constexpr self_type operator-(difference_type offset) const noexcept { return self_type(_accessor, _index - offset); }
		friend constexpr decltype(auto) operator+(difference_type offset, const self_type& iterator) noexcept { return iterator + offset; }

		constexpr decltype(auto) operator++() noexcept { return operator+=(1); }
		constexpr decltype(auto) operator++(int) noexcept
		{
			self_type temp(*this);
			operator++();
			return temp;
		}
		constexpr decltype(auto) operator--() noexcept { return operator+=(-1); }
		constexpr decltype(auto) operator--(int) noexcept
		{
			self_type temp(*this);
			operator--();
			return temp;
		}
		constexpr decltype(auto) operator->() const noexcept { return std::addressof(*this); }
		constexpr decltype(auto) operator[](difference_type offset) const noexcept { return *((*this) + offset); }
		constexpr auto operator<=>(const vector_iterator_impl& other) const noexcept = default;

	public:
		accessor_type* _accessor = nullptr;
		difference_type _index = 0;
	};
}

template<concepts::vectors::accessible _T>
using input_iterator_t = detail::vector_iterator_impl<_T, input_value_wrapper_t<_T>>;

template<concepts::vectors::accessible _T> requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using input_or_output_iterator_t = detail::vector_iterator_impl<_T, input_or_output_value_wrapper_t<_T>>;

template<concepts::vectors::accessible _T>
using input_reverse_iterator_t = std::reverse_iterator<input_iterator_t<_T>>;

template<concepts::vectors::accessible _T> requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using input_or_output_reverse_iterator_t = std::reverse_iterator<input_or_output_iterator_t<_T>>;

NGS_MATH_LA_VECTOR_RANGE_END