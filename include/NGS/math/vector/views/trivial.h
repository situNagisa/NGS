#pragma once

#include "../tag.h"
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
using trivial_vector = NGS_MATH_VECTOR_TAG_NS::retag<NGS_MATH_VECTOR_TAG_NS::trivial, transform_view <_detail::trivial_transformer, adapter_extent, packet<_T>, make_adapter_sentinel>>;

//template<class _T>
//struct trivial_vector : NGS_MATH_VECTOR_TAG_NS::retag<NGS_MATH_VECTOR_TAG_NS::trivial, transform_view <_detail::trivial_transformer, adapter_extent, packet<_T>, make_adapter_sentinel>>
//{
//	NGS_MPL_ENVIRON(trivial_vector);
//public:
//	constexpr explicit trivial_vector(const _T& data) :base_type(data) {}
//	constexpr explicit trivial_vector(_T&& data) : base_type(::std::move(data)) {}
//};

//template<class _T> trivial_vector(_T) -> trivial_vector<_T>;

constexpr auto trivial(auto&& value)
{
	return trivial_vector<type_traits::naked_t<decltype(value)>>(NGS_PP_PERFECT_FORWARD(value));
}
namespace _detail
{
	using zero_vector = NGS_MATH_VECTOR_TAG_NS::retag<NGS_MATH_VECTOR_TAG_NS::zero, trivial_vector<bool>>;
}

inline constexpr _detail::zero_vector zero{ false };

NGS_LIB_MODULE_END