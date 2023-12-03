#pragma once

#include "../defined.h"
#include "../config.h"

NGS_LIB_BEGIN

#undef interface
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
	class _IteratorCategory,
	class _ValueType,
	class _Reference = _ValueType&,
	class _Pointer = _ValueType*,
	class _Difference = std::ptrdiff_t
>
struct interface
{
protected:
	using self_type = interface;
public:
	using iterator_type = _Derived;
	using iterator_category = _IteratorCategory;
	using value_type = _ValueType;
	using reference = _Reference;
	using pointer = _Pointer;
	using difference_type = _Difference;

	constexpr interface() = default;
	constexpr interface(const self_type&) = default;
	constexpr interface(self_type&&) = default;
	constexpr self_type& operator=(const self_type&) = default;
	constexpr self_type& operator=(self_type&&) = default;

	constexpr decltype(auto) operator++()
	{
		NGS_ASSERT_IF_CONSTEXPR(
			(std::invocable<decltype(increment), const _Params&...>),
			"increment must be invocable"
		)
		{
			statics::functional::apply(increment, _packer);
		}
		return _derived();

	}
	constexpr decltype(auto) operator++(int)
	{
		auto copy = _derived();
		operator++();
		return copy;
	}

	constexpr decltype(auto) operator*()const {
		NGS_ASSERT_IF_CONSTEXPR(
			(std::invocable<decltype(dereference), const _Params&...>),
			"dereference must be invocable"
		)
		{
			return statics::functional::apply(dereference, _packer);
		}
	}
protected:
	constexpr decltype(auto) _derived() { return static_cast<iterator_type&>(*this); }
	constexpr decltype(auto) _derived()const { return static_cast<const iterator_type&>(*this); }
};


NGS_LIB_END