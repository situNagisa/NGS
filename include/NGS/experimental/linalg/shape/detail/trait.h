#pragma once

#include "./rank.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


NGS_TCEA_TRAIT_DEFAULT(shape_index, using type = void; );
NGS_TCEA_TRAIT_ALIAS_T(shape_index);
NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(shape_index, index_type);

NGS_TCEA_TRAIT_DEFAULT(shape_ranks, constexpr static auto value = 0ull; );
NGS_TCEA_TRAIT_ALIAS_V(shape_ranks);
NGS_TCEA_TRAIT_HAS_VALUE_OBJECT(shape_ranks, ranks);
template<class IndexType, ::std::size_t... Extent>
struct shape_ranks<::std::extents<IndexType, Extent...>>
{
	constexpr static auto value = ::std::array{ extent{Extent}... };
};

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT_O_2(_extent_at, (::std::convertible_to<rank_t>));
inline constexpr struct
{
	template<class T>
		requires requires(T t, rank_t index) { { _extent_at(NGS_PP_PERFECT_FORWARD(t), index) }; }
	NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(T&& t, rank_t index) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
	{
		return _extent_at(NGS_PP_PERFECT_FORWARD(t), index);
	}
	template<class IndexType, ::std::size_t... Extents>
	NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(const ::std::extents<IndexType, Extents...>& extents, rank_t index) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
	{
		return extents.extent(index);
	}
}extent_at{};

NGS_LIB_MODULE_END