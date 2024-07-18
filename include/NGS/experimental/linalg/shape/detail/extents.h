#pragma once

#include "./extent.h"
#include "./trait.h"
#include "./shape.h"
#include "./algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::integral IndexType, static_extent_t... Extents>
struct extents
{
	NGS_PP_INJECT_BEGIN(extents);
public:
	using index_type = IndexType;
	using size_type = ::std::make_unsigned_t<index_type>;
	using rank_type = rank_t;

	constexpr static NGS_LIB_MODULE_NAME::ranks auto ranks = ::std::array{ extent(Extents)...};

	constexpr extents() = default;

	template<shape T>
		requires (NGS_LIB_MODULE_NAME::rank(ranks) == NGS_LIB_MODULE_NAME::rank<T>()) && (NGS_LIB_MODULE_NAME::dynamic_equal(ranks, shape_ranks_v<T>))
	constexpr explicit(NGS_LIB_MODULE_NAME::is_dynamic_assign(ranks, shape_ranks_v<T>) || (::std::numeric_limits<index_type>::max() < ::std::numeric_limits<shape_index_t<T>>::max()))
	extents(const T& other) noexcept
	{
		constexpr auto indices = NGS_LIB_MODULE_NAME::dynamic_indices<T>();
		for(auto&&[i, index] : ::std::views::enumerate(indices))
		{
			_dynamic_data[i] = NGS_LIB_MODULE_NAME::extent_at(other, index);
		}
	}

	constexpr explicit extents(::std::convertible_to<index_type> auto... extents) noexcept requires
		(::std::is_nothrow_constructible_v<index_type, decltype(extents)> && ...)
		&& ((sizeof...(extents) == NGS_LIB_MODULE_NAME::rank_dynamic(ranks)) || sizeof...(extents) == NGS_LIB_MODULE_NAME::rank(ranks))
		: self_type(::std::array{ static_cast<index_type>(::std::move(extents))...})
	{}
private:
	template<class OtherIndexType, ::std::size_t N>
	consteval static auto _span_concept()
	{
		return (::std::convertible_to<const OtherIndexType&, index_type>)
			&& (::std::is_nothrow_constructible_v<index_type, const OtherIndexType&>)
			&& (N == NGS_LIB_MODULE_NAME::rank_dynamic(ranks) || N == NGS_LIB_MODULE_NAME::rank(ranks));
	}

	template<class OtherIndexType, ::std::size_t... Index>
	constexpr extents(::std::span<OtherIndexType, NGS_LIB_MODULE_NAME::rank_dynamic(ranks)> extents, ::std::index_sequence<Index...>) noexcept
		: _dynamic_data{::std::as_const(extents[Index])...}
	{}

	template<class OtherIndexType, ::std::size_t N, ::std::size_t... Index>
	constexpr extents(::std::span<OtherIndexType, N> extents, ::std::index_sequence<Index...>) noexcept
		: _dynamic_data{ ::std::as_const(extents[NGS_LIB_MODULE_NAME::dynamic_index_inv(ranks, Index)])... }
	{}
public:
	template<class OtherIndexType, ::std::size_t N>
		requires (_span_concept<OtherIndexType, N>())
	constexpr explicit(N != NGS_LIB_MODULE_NAME::rank_dynamic(ranks))
		extents(::std::span<OtherIndexType, N> extents) noexcept
		: self_type(extents, ::std::make_index_sequence<NGS_LIB_MODULE_NAME::rank_dynamic(ranks)>{})
	{}

	template<class OtherIndexType, ::std::size_t N>
		requires (_span_concept<OtherIndexType, N>())
	constexpr explicit(N != NGS_LIB_MODULE_NAME::rank_dynamic(ranks))
		extents(const ::std::array<OtherIndexType, N>& extents) noexcept
		: self_type(extents, ::std::make_index_sequence<NGS_LIB_MODULE_NAME::rank_dynamic(ranks)>{})
	{}

	constexpr index_type extent_at(rank_type index) const noexcept
	{
		NGS_ASSERT_IF_CONSTEVAL(index < NGS_LIB_MODULE_NAME::rank(ranks));
		if constexpr(NGS_LIB_MODULE_NAME::rank_dynamic(ranks) == 0)
		{
			return static_cast<index_type>(ranks[index]);
		}
		else if constexpr(NGS_LIB_MODULE_NAME::rank_dynamic(ranks) == NGS_LIB_MODULE_NAME::rank(ranks))
		{
			return _dynamic_data[index];
		}
		else
		{
			if (ranks[index].is_dynamic())
			{
				return _dynamic_data[NGS_LIB_MODULE_NAME::dynamic_index(ranks, index)];
			}
		}
		if (extent e = NGS_LIB_MODULE_NAME::static_extent(ranks, index); e.is_static())
		{
			return e.value();
		}
		constexpr auto indices = []
			{
				::std::array<index_type, NGS_LIB_MODULE_NAME::rank(ranks)> result{};
				auto dynamic_size = 0ul;
				::std::ranges::copy(
					::std::views::iota(0)
					| ::std::views::take(NGS_LIB_MODULE_NAME::rank(ranks))
					| ::std::views::transform([dynamic_size](auto i) mutable
						{
							if (ranks[i].is_dynamic())
							{
								dynamic_size++;
								return dynamic_size - 1;
							}
							return 0;
						}),
					::std::ranges::begin(result)
				);
				return result;
			}();
		return _dynamic_data[indices[index]];
	}

	::std::array<index_type, NGS_LIB_MODULE_NAME::rank_dynamic(ranks)> _dynamic_data;
};

NGS_LIB_MODULE_END