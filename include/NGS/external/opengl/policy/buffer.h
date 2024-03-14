#pragma once

#include "../enum.h"
#include "../context.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::derived_from<contexts::unknown_buffer> Buffer,::std::ranges::contiguous_range Range>
	requires basic::bindable<Buffer>
struct buffer
{
	NGS_MPL_ENVIRON_BEGIN(buffer);
public:
	using context_type = Buffer;
	using range_type = Range;
	using subrange_type = ::std::ranges::subrange<::std::ranges::iterator_t<range_type>, ::std::ranges::sentinel_t<range_type>>;

	buffer(context_type&& context, enums::usage usage, auto&&... args) requires ::std::constructible_from<range_type,decltype(args)...>
		: _context(::std::move(context))
		, _range(NGS_PP_PERFECT_FORWARD(args)...)
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		, _current_size(::std::ranges::size(_range))
#endif
	{
		basic::bind(_context);
		algorithm::buffer_allocate(_context, sizeof(::std::ranges::range_value_t<range_type>) * ::std::ranges::size(_range), usage);
	}
	explicit(false) buffer(enums::usage usage, auto&&... args) requires ::std::constructible_from<range_type, decltype(args)...>
		: self_type(context_type{}, usage, NGS_PP_PERFECT_FORWARD(args)...)
	{}

	void describe(enums::usage usage)
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		_current_size = ::std::ranges::size(_range);
#endif
		algorithm::buffer_describe(_context, _range, usage);
	}

	void submit(auto&&... args)
		requires ::std::constructible_from<subrange_type,decltype(args)...>
	{
		subrange_type subrange{NGS_PP_PERFECT_FORWARD(args)...};
		auto offset = ::std::ranges::distance(::std::ranges::begin(_range), ::std::ranges::begin(NGS_PP_PERFECT_FORWARD(subrange)));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		NGS_ASSERT(offset + ::std::ranges::size(NGS_PP_PERFECT_FORWARD(subrange)) <= _current_size);
#endif
		algorithm::buffer_submit(_context, NGS_PP_PERFECT_FORWARD(subrange), offset);
	}
	void submit(::std::ranges::range_difference_t<range_type> offset,::std::ranges::range_size_t<range_type> count)
	{
		self_type::submit(::std::ranges::begin(_range) + offset, ::std::ranges::begin(_range) + offset + count);
	}
	void submit() { self_type::submit(_range); }

	constexpr auto&& get_context() const { return _context; }
	constexpr auto&& data() { return _range; }
	constexpr auto&& data() const { return _range; }

private:
	context_type _context;
	range_type _range;
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	::std::size_t _current_size = 0;
#endif
};

template<cpt::derived_from_specialization<buffer> Buffer>
using buffer_range_t = typename type_traits::object_t<Buffer>::range_type;

template<cpt::derived_from_specialization<buffer> Buffer>
using buffer_value_t = ::std::ranges::range_value_t<buffer_range_t<Buffer>>;

NGS_LIB_MODULE_END