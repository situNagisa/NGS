#pragma once

#include "./defined.h"

NGS_STL_ITERATOR_BEGIN

/**
 * \code
 * std::input_or_output_iterator :
 * std::movable
 * std::weakly_incrementable
 * requires
 * i++,++i
 * { *i } -> can_reference
 * \endcode
*/
/**
 * \brief 满足\code std::input_or_output_iterator \endcode 的迭代器
 * \tparam _Derived
 * \tparam _Difference
 *
*/
template<
	class _Derived,
	class _Difference = std::ptrdiff_t
>
struct input_or_output
{
protected:
	using self_type = input_or_output;
public:
	using iterator_type = _Derived;
	using difference_type = _Difference;

	constexpr input_or_output() = default;
	constexpr input_or_output(const self_type&) = default;
	constexpr input_or_output(self_type&&) = default;
	constexpr self_type& operator=(const self_type&) = default;
	constexpr self_type& operator=(self_type&&) = default;

	constexpr decltype(auto) operator++(int)
	{
		auto copy = _derived();
		++_derived();
		return copy;
	}

	//constexpr iterator_type& operator++() { return ++_derived(); }
	//constexpr decltype(auto) operator*()const { return *_derived(); }
protected:
	constexpr decltype(auto) _derived() { return static_cast<iterator_type&>(*this); }
	constexpr decltype(auto) _derived()const { return static_cast<const iterator_type&>(*this); }
};


NGS_STL_ITERATOR_END