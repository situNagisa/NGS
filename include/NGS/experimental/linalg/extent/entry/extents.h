#pragma once

#include "../trait.h"
#include "../concept.h"
#include "../algorithm.h"
#include "./defined.h"

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

	constexpr extents() = default;
	template<class OtherIndexType, traits::static_extent_t... OtherExtents>
	constexpr explicit(
		((Extents != traits::dynamic_extent && OtherExtents == traits::dynamic_extent) || ...)
		|| (::std::numeric_limits<index_type>::max() < ::std::numeric_limits<OtherIndexType>::max())
		) extents(const extents<OtherIndexType, OtherExtents...>& other)
		requires (sizeof...(OtherExtents) == self_type::rank())
		&& ((Extent))


	::std::array<index_type, self_type::rank_dynamic()> _dynamic_data;
};

NGS_LIB_MODULE_END