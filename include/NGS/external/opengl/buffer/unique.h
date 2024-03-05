#pragma once

#include "./buffer.h"
#include "./algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::buffer_target Target,class ValueType>
struct unique_buffer : buffer<Target>
{
	NGS_MPL_ENVIRON(unique_buffer);
public:
	using value_type = ValueType;
	using range_type = ::std::vector<value_type>;
	using difference_type = ::std::ranges::range_difference_t<range_type>;
	using size_type = ::std::ranges::range_size_t<range_type>;

	unique_buffer(enums::usage usage)
		: _data()
	{
		basic::bind(*this);
		NGS_LIB_MODULE_NAME::allocate(*this, sizeof(value_type) * _data.size(), usage);
	}

	unique_buffer(self_type&&) = default;
	using base_type::operator=;


	constexpr auto&& data() { return _data; }
	constexpr auto&& data()const { return _data; }

	void update(enums::usage usage)
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		_current_size = _data.size();
#endif
		NGS_LIB_MODULE_NAME::describe(*this, _data, usage);
	}
	void submit(difference_type begin, size_type count)const
	{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		NGS_ASSERT(begin + count <= _current_size);
#endif
		NGS_LIB_MODULE_NAME::submit(*this, ::std::span<const value_type>(_data.begin() + begin, count), begin);
	}
private:
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	size_type _current_size = 0;
#endif
	range_type _data{};
};

NGS_LIB_MODULE_END