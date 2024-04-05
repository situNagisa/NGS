#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::ranges::range Range>
struct pusher
{
	NGS_MPL_ENVIRON_BEGIN(pusher);
public:
	using range_forward_type = Range;
	using range_type = type_traits::object_t<range_forward_type>;

private:
	constexpr explicit(false) pusher(int, auto&& range, ::std::ranges::range_difference_t<range_type> size = 0)
		: _range(NGS_PP_PERFECT_FORWARD(range))
		, _size(size)
	{}
public:
	constexpr explicit(false) pusher(auto&& range, ::std::ranges::range_difference_t<range_type> size = 0) requires ::std::constructible_from<range_type,decltype(range)>
		: pusher(0, NGS_PP_PERFECT_FORWARD(range), size)
	{}
	constexpr explicit(false) pusher(const range_type& range, ::std::ranges::range_difference_t<range_type> size = 0) requires ::std::copy_constructible<range_type>
		: pusher(0, range, size)
	{}
	constexpr explicit(false) pusher(range_type&& range, ::std::ranges::range_difference_t<range_type> size = 0) requires ::std::move_constructible<range_type>
		: pusher(0, ::std::move(range), size)
	{}
	constexpr explicit(false) pusher(range_forward_type range, ::std::ranges::range_difference_t<range_type> size = 0) requires ::std::is_reference_v<range_forward_type>
		: pusher(0, range, size)
	{}

	constexpr auto push_range(const ::std::ranges::range auto& range)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(range)>,::std::ranges::iterator_t<range_type>>
	{
		auto result = ::std::ranges::copy(range, ::std::ranges::next(::std::ranges::begin(_range),_size));
		_size += ::std::ranges::distance(range);
		return result;
	}
	constexpr decltype(auto) push_range(::std::initializer_list<::std::ranges::range_value_t<range_type>>&& range)
	{
		return self_type::push_range(range);
	}

	constexpr auto size() const { return _size; }
	constexpr void resize(::std::ranges::range_difference_t<range_type> size) { _size = size; }

	range_forward_type _range;
	::std::ranges::range_difference_t<range_type> _size;
};

template<::std::ranges::range Range>
pusher(Range&& range, ::std::ranges::range_difference_t<Range> size = 0) -> pusher<Range>;

template<::std::ranges::range Range>
pusher(const Range& range, ::std::ranges::range_difference_t<Range> size = 0) -> pusher<Range>;

template<::std::ranges::range Range>
pusher(Range& range, ::std::ranges::range_difference_t<Range> size = 0) -> pusher<Range&>;



NGS_LIB_MODULE_END
