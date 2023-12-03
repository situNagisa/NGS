#pragma once

#include "./attribute.h"

NGS_LIB_MODULE_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept CBinder = requires
{
	{ _O::attribute_count } -> ::std::convertible_to<size_t>;
	{ _O::formats } -> ::std::convertible_to<::std::array<vk::Format, _O::attribute_count>>;
	{ _O::input_rate } -> ::std::convertible_to<vk::VertexInputRate>;
		requires mpl::mstruct::CStructure<typename _O::structure_type>;
};

template<vk::VertexInputRate _InputRate>
using input_rate_type = ccpt::constant_<vk::VertexInputRate, _InputRate>;

namespace detail {

	template<vk::VertexInputRate _InputRate, CAttribute... _Attributes>
	struct binder
	{
		using structure_type = mpl::mstruct::structure<typename _Attributes::variable_type...>;
		constexpr static size_t attribute_count = sizeof...(_Attributes);
		constexpr static ::std::array<vk::Format, attribute_count> formats = { _Attributes::format... };
		constexpr static auto input_rate = _InputRate;
	};

	template<class...>struct make_binder;

	/// @brief 
	///
	template<class... _Types> using make_binder_t = typename make_binder<_Types...>::type;

	using binder_default_input_rate_t = ccpt::constant_<vk::VertexInputRate, vk::VertexInputRate::eVertex>;

	template<class _First, class... _Rest>
	struct make_binder<_First, _Rest...>
	{
		constexpr static auto make()
		{
			if constexpr (ccpt::constant<_First, vk::VertexInputRate>)
			{
				return NGS_ declval<binder<
					_First::value,
					::std::conditional_t<CAttribute<_Rest>, _Rest, attribute<_Rest>>...
					>>();
			}
			else
			{
				return NGS_ declval<binder<
					binder_default_input_rate_t::value,
					::std::conditional_t<CAttribute<_First>, _First, attribute<_First>>,
					::std::conditional_t<CAttribute<_Rest>, _Rest, attribute<_Rest>>...
					>>();
			}
		}
		using type = type_traits::naked_t<decltype(make())>;
	};
}

template<class... _Types> using binder = detail::make_binder_t<_Types...>;
template<vk::VertexInputRate _InputRate, class... _Types> using binder_c = binder<input_rate_type<_InputRate>, _Types...>;

NGS_LIB_MODULE_END