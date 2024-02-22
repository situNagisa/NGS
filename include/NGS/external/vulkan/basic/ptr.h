#pragma once

#include "./vulkan.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
struct vulkan_ptr
{
	NGS_MPL_ENVIRON_BEGIN(vulkan_ptr);
public:
	using value_type = _T;

	constexpr vulkan_ptr() = default;
	constexpr vulkan_ptr(const value_type& data) : _data(new value_type(data)) { }
	constexpr vulkan_ptr(value_type&& data) : _data(new value_type(::std::move(data))) { }
	constexpr vulkan_ptr(self_type&& other) noexcept
		: _data(other._data)
	{
		other._data = nullptr;
	}
	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (this == &other)
			return *this;
		delete _data;
		_data = other._data;
		other._data = nullptr;
		return *this;
	}
	constexpr self_type& operator=(const value_type& data)
	{
		*_data = data;
		return *this;
	}
	constexpr self_type& operator=(value_type&& data)
	{
		*_data = ::std::move(data);
		return *this;
	}

	constexpr ~vulkan_ptr()
	{
		delete _data;
	}

	constexpr auto data()const { return _data; }

	constexpr auto vulkan_data() requires vulkan_layout_info<value_type>
	{
		return &NGS_LIB_NAME::to_vulkan(*_data);
	}
	constexpr auto vulkan_data() const requires vulkan_layout_info<value_type>
	{
		return &NGS_LIB_NAME::to_vulkan(*_data);
	}

	value_type* _data = nullptr;
};
static_assert(sizeof(vulkan_ptr<int>) == sizeof(const void*), "memory layout error");


NGS_LIB_END