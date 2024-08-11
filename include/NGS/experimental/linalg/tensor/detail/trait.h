#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_DEFAULT_TYPE(tensor_extents, void);
NGS_TCEA_TRAIT_ALIAS_T(tensor_extents);
NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(tensor_extents, extents_type);

template<class T, class Shape>
concept access_index_sequence = shapes::shape<Shape> &&
	//::std::constructible_from<::std::array<shapes::shape_index_t<Shape>, shapes::rank(shapes::shape_ranks_v<Shape>)>, T>;
	::std::ranges::input_range<T> && shapes::common_index<shapes::shape_index_t<Shape>, ::std::ranges::range_value_t<T>>;

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(_access, (access_index_sequence<tensor_extents_t<T>>));

namespace _details
{
	template<class T, class Extents, class Layout, class Accessor>
	void derived_from_mdspan(const ::std::mdspan<T, Extents, Layout, Accessor>&);

	template<class T>
	concept is_multi_span = requires(T t) { { _details::derived_from_mdspan(NGS_PP_PERFECT_FORWARD(t)) }; };
}

inline constexpr struct access_cpo
{
	static decltype(auto) basic_access(auto&& target, auto&& indices) noexcept
	{
		if constexpr (requires{ _access(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(indices)); })
		{
			return _access(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(indices));
		}
		else if constexpr (requires{ NGS_PP_PERFECT_FORWARD(target)[NGS_PP_PERFECT_FORWARD(indices)]; })
		{
			return NGS_PP_PERFECT_FORWARD(target)[NGS_PP_PERFECT_FORWARD(indices)];
		}
		else
		{
			static_assert(concepts::none<decltype(target), decltype(indices)>, "No access method found for target");
		}
	}

	template<class T>
		requires shapes::shape<tensor_extents_t<T>>
	static decltype(auto) access(T&& t, access_index_sequence<tensor_extents_t<T>> auto&& indices) noexcept
	{
		using shape_type = tensor_extents_t<T>;
		using index_type = shapes::shape_index_t<shape_type>;
		constexpr auto rank = shapes::rank(shapes::shape_ranks_v<shape_type>);
		if constexpr (
			_details::is_multi_span<T>
			&& !::std::constructible_from<const ::std::array<index_type, rank>&, decltype(indices)>
			&& !::std::constructible_from<::std::span<index_type, rank>, decltype(indices)>
			)
		{
			return access_cpo::basic_access(NGS_PP_PERFECT_FORWARD(t), indices | ::std::ranges::to<::std::vector<index_type>>());
		}
		else
		{
			return access_cpo::basic_access(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(indices));
		}
	}

	template<class T, class... OtherIndexType>
		requires shapes::shape<tensor_extents_t<T>> && (shapes::common_index<shapes::shape_index_t<tensor_extents_t<T>>, OtherIndexType> && ...)
	NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(T&& t, OtherIndexType... indices) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
	{
		using shape_type = tensor_extents_t<T>;
		using index_type = shapes::shape_index_t<shape_type>;
		constexpr auto rank = shapes::rank(shapes::shape_ranks_v<shape_type>);

#ifdef __cpp_multidimensional_subscript
		if constexpr (requires{ NGS_PP_PERFECT_FORWARD(t)[NGS_PP_PERFECT_FORWARD(indices)...]; })
		{
			return NGS_PP_PERFECT_FORWARD(t)[NGS_PP_PERFECT_FORWARD(indices)...];
		}
		else
#endif
		{
			return access_cpo::access(NGS_PP_PERFECT_FORWARD(t), ::std::array{ static_cast<index_type>(indices) ... });
		}
	}

	template<class T>
		requires shapes::shape<tensor_extents_t<T>>
	NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(T&& t, access_index_sequence<tensor_extents_t<T>> auto&& indices) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
	{
		return access_cpo::access(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(indices));
	}

	template<class T>
		requires shapes::shape<tensor_extents_t<T>>
	NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(
		T&& t, 
		const ::std::array<shapes::shape_index_t<tensor_extents_t<T>>, shapes::rank(shapes::shape_ranks_v<tensor_extents_t<T>>)>& indices
		) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
	{
		return access_cpo::access(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(indices));
	}
} access{};

NGS_LIB_MODULE_END