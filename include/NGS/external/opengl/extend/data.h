#pragma once

#include "../basic.h"
#include "../context.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::derived_from<contexts::unknown_buffer> Buffer, class ValueType>
	requires basic::bindable<Buffer>
struct data_buffer
{
	NGS_MPL_ENVIRON_BEGIN(data_buffer);
public:
	using value_type = ValueType;
	using range_type = ::std::vector<value_type>;
	using difference_type = ::std::ranges::range_difference_t<range_type>;
	using size_type = ::std::ranges::range_size_t<range_type>;
	using buffer_type = Buffer;

	data_buffer(buffer_type&& buffer, enums::usage usage)
		: _buffer(::std::move(buffer))
	{
		basic::bind(_buffer);
		algorithm::buffer_allocate(_buffer, sizeof(value_type) * _data.size(), usage);
	}

	explicit(false) data_buffer(enums::usage usage) requires ::std::constructible_from<buffer_type>
		: self_type({},usage)
	{}

	constexpr auto&& buffer() { return _buffer; }
	constexpr auto&& buffer() const { return _buffer; }

	constexpr auto&& data() { return _data; }
	constexpr auto&& data()const { return _data; }

	void update(enums::usage usage)
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		_current_size = _data.size();
#endif
		algorithm::buffer_describe(_buffer, _data, usage);
	}
	void submit(difference_type begin, size_type count)const
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		NGS_ASSERT(begin + count <= _current_size);
#endif
		algorithm::buffer_submit(_buffer, ::std::span<const value_type>(_data.begin() + begin, count), begin);
	}
private:
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	size_type _current_size = 0;
#endif
	buffer_type _buffer;
	range_type _data{};
};

NGS_LIB_MODULE_END