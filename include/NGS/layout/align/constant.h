#pragma once

#include "./concept.h"
#include "./valid_align.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t Priority,::std::size_t Align>
struct align_constant
{
	static constexpr ::std::size_t priority() { return Priority; }
	static constexpr ::std::size_t align() { return Align; }
};

struct align_t
{
	NGS_MPL_ENVIRON_BEGIN(align_t);
public:

	constexpr align_t() = default;
	constexpr align_t(::std::size_t priority,::std::size_t align)
		: _priority(priority)
		, _align(align)
	{
		if (!::std::is_constant_evaluated())
		{
			NGS_ASSERT(is_valid_align(*this));
		}
	}
	constexpr explicit(false) align_t(::std::size_t align) : self_type(align,align){}

	constexpr explicit(false) align_t(NGS_LIB_MODULE_NAME::align auto&& other)
		: self_type(NGS_PP_PERFECT_FORWARD(other).priority(), NGS_PP_PERFECT_FORWARD(other).align())
	{}

	constexpr self_type& operator=(NGS_LIB_MODULE_NAME::align auto&& other)
	{
		_priority = NGS_PP_PERFECT_FORWARD(other).priority();
		_align = NGS_PP_PERFECT_FORWARD(other).align();
		return *this;
	}

	constexpr ::std::size_t priority()const  { return _priority; }
	constexpr ::std::size_t align() const { return _align; }

	::std::size_t _priority;
	::std::size_t _align;
};

NGS_LIB_MODULE_END
