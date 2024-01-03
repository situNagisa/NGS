#pragma once

#include "../iterator.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr const auto& operator()(index_t, auto&& value)const noexcept
		{
			return value;
		}
	}trivial_transformer{};
}

template<class _T>
struct trivial_vector : transform_view <_detail::trivial_transformer, adapter_extent, packet<_T>, make_adapter_sentinel>
{
	using base_type = transform_view <_detail::trivial_transformer, adapter_extent, packet<_T>, make_adapter_sentinel>;

	constexpr explicit trivial_vector(const _T& data) :base_type(data) {}
	constexpr explicit trivial_vector(_T&& data) : base_type(::std::move(data)) {}
};

template<class _T> trivial_vector(_T) -> trivial_vector<_T>;

NGS_LIB_MODULE_END