#pragma once

#include "../../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template <auto Target>
	void derived_from_basic_buffer(const NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::buffer<Target>&);

	template <class T>
	concept buffer_context = requires(const T& obj) { _detail::derived_from_basic_buffer(obj); };

}

template<_detail::buffer_context Buffer,::std::ranges::contiguous_range Range>
struct buffer
{
	NGS_MPL_ENVIRON_BEGIN(buffer);
public:
	using context_type = Buffer;
	using range_type = Range;
	using subrange_type = ::std::ranges::subrange<::std::ranges::iterator_t<range_type>, ::std::ranges::sentinel_t<range_type>>;
private:
	buffer(int, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&& range) requires ::std::constructible_from<range_type,decltype(range)>
		: _context()
		, _range(NGS_PP_PERFECT_FORWARD(range))
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		, _current_size(::std::ranges::size(_range))
#endif
	{
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_context);
		//_context.allocate(sizeof(::std::ranges::range_value_t<range_type>) * ::std::ranges::size(_range), usage);
		self_type::describe(usage);
	}
public:
	explicit(false) buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&&... range_args) requires ::std::constructible_from<range_type, decltype(range_args)...>
		: self_type(0, usage, range_type{NGS_PP_PERFECT_FORWARD(range_args)...})
	{}

	buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, const range_type& range) requires ::std::copy_constructible<range_type>
		: self_type(0, usage, range)
	{}
	buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, range_type&& range) requires ::std::move_constructible<range_type>
		: self_type(0, usage, ::std::move(range))
	{}

	void describe(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage)
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		_current_size = ::std::ranges::size(_range);
#endif
		_context.describe(_range, usage);
	}

	void submit(auto&&... args)
		requires ::std::constructible_from<subrange_type,decltype(args)...>
	{
		subrange_type subrange{NGS_PP_PERFECT_FORWARD(args)...};
		auto offset = ::std::ranges::distance(::std::ranges::begin(_range), ::std::ranges::begin(NGS_PP_PERFECT_FORWARD(subrange)));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		NGS_ASSERT(offset + ::std::ranges::size(NGS_PP_PERFECT_FORWARD(subrange)) <= _current_size);
#endif
		_context.submit(NGS_PP_PERFECT_FORWARD(subrange), offset);
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