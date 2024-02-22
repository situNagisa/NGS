#pragma once

#include "./vulkan.h"
#include "./defined.h"

NGS_LIB_BEGIN

using size_t = uint32_t;

/// \note need `empty base optimization`
template<class _T, class _SizeType = size_t>
struct alignas(sizeof(const void*)) vulkan_range : ::std::ranges::view_interface<vulkan_range<_T, _SizeType>>
{
	NGS_MPL_ENVIRON_BEGIN(vulkan_range);
public:
	using value_type = _T;
	using size_type = _SizeType;

	constexpr vulkan_range() = default;
	constexpr explicit(false) vulkan_range(size_type size) : _count(size), _data(new value_type[size]) {}
	constexpr vulkan_range(::std::initializer_list<value_type> data) : _count(static_cast<size_type>(data.size())), _data(new value_type[data.size()]) { ::std::ranges::copy(data, _data); }
	constexpr vulkan_range(const self_type& other)
		: _count(other._count)
		, _data(new value_type[other._count])
	{
		::std::ranges::copy(other, _data);
	}
	constexpr self_type& operator=(const self_type& other)
	{
		if (this == &other)
			return *this;
		_count = other._count;
		_data = new value_type[other._count];
		::std::ranges::copy(other, _data);
		return *this;
	}

	constexpr vulkan_range(self_type&& other) noexcept
		: _count(other._count)
		, _data(other._data)
	{
		other._data = nullptr;
	}
	constexpr self_type& operator=(self_type&& other) noexcept
	{
		if (this == &other)
			return *this;
		delete[] _data;
		_count = other._count;
		_data = other._data;
		other._data = nullptr;
		return *this;
	}

	constexpr vulkan_range(::std::ranges::sized_range auto&& data)
		requires
	::std::convertible_to<::std::ranges::range_value_t<decltype(data)>, value_type>
		: _count(::std::ranges::size(data))
		, _data(new value_type[_count])
	{
		::std::ranges::copy(NGS_PP_PERFECT_FORWARD(data), _data);
	}
	constexpr self_type& operator=(::std::ranges::sized_range auto&& data)
		requires ::std::convertible_to<::std::ranges::range_value_t<decltype(data)>, value_type>
	{
		delete[] _data;
		_count = ::std::ranges::size(data);
		_data = new value_type[_count];
		::std::ranges::copy(NGS_PP_PERFECT_FORWARD(data), _data);
		return *this;
	}

	constexpr ~vulkan_range()
	{
		delete[] _data;
	}

	constexpr auto begin() { return _data; }
	constexpr auto end() { return _data + _count; }
	constexpr auto begin() const { return _data; }
	constexpr auto end() const { return _data + _count; }

	constexpr auto size()const { return _count; }
	constexpr auto data()const { return _data; }

	constexpr auto vulkan_data() requires vulkan_layout_info<value_type>
	{
		return &NGS_LIB_NAME::to_vulkan(*_data);
	}
	constexpr auto vulkan_data() const requires vulkan_layout_info<value_type>
	{
		return &NGS_LIB_NAME::to_vulkan(*_data);
	}

	constexpr void assign(size_type index, const value_type& value)
	{
		if (!::std::is_constant_evaluated())
			NGS_ASSERT(index < _count);
		_data[index] = value;
	}
	constexpr void assign(size_type index, value_type&& value)
	{
		if (!::std::is_constant_evaluated())
			NGS_ASSERT(index < _count);

		_data[index] = ::std::move(value);
	}
	size_type _count = 0;
	value_type* _data = nullptr;
};
static_assert(sizeof(vulkan_range<int>) == 2 * sizeof(const void*), "memory layout error");
static_assert(alignof(vulkan_range<int>) == sizeof(const void*), "memory layout error");
static_assert(offsetof(vulkan_range<int>, _count) == 0, "memory layout error");

template<class _T, class _S> requires vulkan_info<_T>
constexpr auto to_vulkan_vector(const vulkan_range<_T, _S>& range)
{
	using result_type = ::std::vector<NGS_LIB_NAME::vulkan_info_t<_T>>;
	if constexpr (vulkan_member_info<_T>)
	{
		result_type result(range.size());
		::std::ranges::transform(range, result.begin(), [](const auto& value) { return NGS_LIB_NAME::to_vulkan(value); });
		return result;
	}
	else if constexpr (vulkan_layout_info<_T>)
	{
		return result_type(range.vulkan_data(), range.vulkan_data() + range.size());
	}

}

NGS_LIB_END