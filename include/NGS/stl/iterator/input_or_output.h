#pragma once

#include "./defined.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \brief 满足\code std::input_or_output_iterator \endcode 的迭代器
 * \tparam _Derived
 * \tparam _Difference
 *
 * \note 要求`_Derived`具有成员函数函数
 * \code
 * iterator_type& _increment()
 * can_reference auto _dereference()const
 * \endcode
 *
 * \code
 * example
 *	struct iterator : input_or_output<iterator>
 *	{
 *		NGS_MPL_ENVIRON(iterator);
 *	public:
 *		using base_type::base_type;
 *
 *		constexpr iterator& _increment() { return *this; }
 *		constexpr decltype(auto) _dereference()const { return 0; }
 *
 *	};
 *	static_assert(std::input_or_output_iterator<iterator>);
 * \endcode
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

	///for \code std::weakly_incrementable \endcode

	/// \code std::default_initializable \endcode
	constexpr input_or_output() = default;
	/// \code std::movable \endcode
	constexpr input_or_output(self_type&&) = default;
	constexpr decltype(auto) operator=(self_type&&) = default;

	/// \code requires  i++,++i \endcode 
	constexpr iterator_type& operator++()
	{
		return _derived()._increment();
	}
	constexpr decltype(auto) operator++(int)const
	{
		auto copy = _derived();
		_derived().increment();
		return copy;
	}

	///for \code std::input_or_output_iterator \endcode

	///\code requires { *i } -> can_reference \endcode
	constexpr decltype(auto) operator*()const { return _derived()._dereference(); }


	constexpr input_or_output(const self_type&) = default;
	constexpr decltype(auto) operator=(const self_type&) = default;

protected:
	constexpr decltype(auto) _derived() { return static_cast<iterator_type&>(*this); }
	constexpr decltype(auto) _derived()const { return static_cast<const iterator_type&>(*this); }
};


NGS_STL_ITERATOR_END