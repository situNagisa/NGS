#pragma once

#include "../container.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
struct scalar : basic_vector
{
	NGS_MPL_ENVIRON_BEGIN(scalar);
public:
	using value_type = _T;
	constexpr static auto extent = adapter_extent;

	constexpr scalar() = default;
	constexpr explicit scalar(const value_type& data) :_data(data) {}
	constexpr explicit scalar(value_type&& data) : _data(::std::move(data)) {}

	constexpr auto operator[](index_t index)const { return _data; }

	constexpr auto begin()const { return &_data; }
	constexpr auto end()const { return &_data + 1; }

	NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();
public:
	value_type _data{};
};

template<class _T> scalar(_T) -> scalar<_T>;

NGS_LIB_MODULE_END