#pragma once

#include "../trait.h"
#include "../concept.h"
#include "../algorithm.h"
#include "./defined.h"
#include <mdspan>

NGS_LIB_MODULE_BEGIN

template<::std::integral IndexType, traits::static_extent_t... Extents>
struct extents
{
	NGS_PP_INJECT_BEGIN(extents);
public:
	using index_type = IndexType;
	using size_type = ::std::make_unsigned_t<index_type>;
	using rank_type = traits::rank_t;

	consteval static auto _rank_data() {
		if constexpr (sizeof...(Extents) == 0)
		{
			return ::std::array<traits::static_extent_t, 0>{};
		}
		else
		{
			return ::std::array<traits::static_extent_t, sizeof...(Extents)>{ Extents... };
		}
	}

	consteval static rank_type rank() { return sizeof...(Extents); }
	consteval static rank_type rank_dynamic()
	{
		return ::std::ranges::count_if(_rank_data(), [](auto e) { return e == traits::dynamic_extent; });
	}
	consteval static rank_type rank_adaptor()
	{
		return ::std::ranges::count_if(_rank_data(), [](auto e) { return e == traits::adaptor_extent; });
	}

	constexpr static traits::static_extent_t static_extent(rank_type i)
	{
		return _rank_data()[i];
	}

	constexpr static auto _dynamic_indexes()
	{
		auto result = ::std::array<traits::static_extent_t, self_type::rank_dynamic()>{};
		::std::ranges::copy(_rank_data() | ::std::views::filter([](auto e) { return e == traits::dynamic_extent; }), result.begin());
		return result;
	}

	constexpr extents() = default;

	template<class OtherIndexType, traits::static_extent_t... OtherExtents>
		requires (sizeof...(OtherExtents) == self_type::rank()) && ((OtherExtents == traits::dynamic_extent || Extents == traits::dynamic_extent || Extents == OtherExtents) && ...)
	constexpr
	explicit(((Extents != traits::dynamic_extent && OtherExtents == traits::dynamic_extent) || ...)|| (::std::numeric_limits<index_type>::max() < ::std::numeric_limits<OtherIndexType>::max()))
		extents(const extents<OtherIndexType, OtherExtents...>& other) noexcept
	{
		for (auto&& [index, extent] : _dynamic_data | ::std::views::enumerate)
		{
			extent = other.extent(_dynamic_indexes()[index]);
		}
	}

	template<class... OtherIndexTypes>
		requires
		(::std::convertible_to<OtherIndexTypes, IndexType> && ...)
		&& (::std::is_nothrow_constructible_v<IndexType, OtherIndexTypes> && ...)
		&& ((sizeof...(OtherIndexTypes) == self_type::rank_dynamic()) || (sizeof...(OtherIndexTypes) == self_type::rank()))
	constexpr explicit extents(OtherIndexTypes... other) noexcept
			: self_type(::std::array<IndexType, sizeof...(OtherIndexTypes)>{static_cast<IndexType>(::std::move(other))...})
	{
	}

	template<class OtherIndexType, ::std::size_t N>
		requires
		(::std::convertible_to<const OtherIndexType&, IndexType>)
		&& (::std::is_nothrow_constructible_v<IndexType, const OtherIndexType&>)
		&& (N == self_type::rank_dynamic() || N == self_type::rank())
	constexpr explicit(N != self_type::rank_dynamic())
		extents(::std::span<OtherIndexType, N> other) noexcept
	{
		if constexpr(N == self_type::rank_dynamic())
		{
			
		}
		else
		{
			::std::extents
		}
	}


	::std::array<index_type, self_type::rank_dynamic()> _dynamic_data;
};

NGS_LIB_MODULE_END