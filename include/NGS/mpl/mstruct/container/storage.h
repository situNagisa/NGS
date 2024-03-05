#pragma once

#include "./variable.h"
#include "./struct.h"
#include "../storage.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace  _detail
{
	template<class Left,class Right = Left>
	concept assignable_from = ::std::assignable_from<Left&, const Right&> || ::std::ranges::output_range<Left&, ::std::ranges::range_value_t<Right>>;

	template<class Left,class Right>
	constexpr decltype(auto) assign(Left& left, const Right& right)
	{
		if constexpr (::std::assignable_from<Left&,const Right&>)
		{
			left = right;
		}
		else if constexpr (::std::ranges::output_range<Left&,::std::ranges::range_value_t<Right>>)
		{
			::std::ranges::copy(right, ::std::ranges::begin(left));
		}
		else
		{
			static_assert(cpt::none<Left>,"can't assign");
		}
	}

	template<class T>
	struct storage_constructor_param
	{
		using type = T;
	};
	template<variables::variable T>
	struct storage_constructor_param<T> { using type = variables::variable_value_t<T>; };

	template<class T>
	using storage_constructor_param_t = typename storage_constructor_param<T>::type;
}

template<layout::align auto Align, class... Ts>
struct alignas(basic::struct_align_v<basic_struct<Align, make_fields_t<Ts...>>>.align()) storage : basic_struct<Align,make_fields_t<Ts...>>
{
	NGS_MPL_ENVIRON2(storage, basic_struct<Align, make_fields_t<Ts...>>);
public:
	template<class... Bases>
	struct inherit : _detail::inherit<self_type, Bases...>::type {};

	constexpr storage() = default;
	storage(const _detail::storage_constructor_param_t<Ts>&... data) requires (_detail::assignable_from<_detail::storage_constructor_param_t<Ts>> && ...)
	{
		[&]<::std::size_t... Index>(::std::index_sequence<Index...>){
			(_detail::assign(storages::get<Index>(*this),data), ...);
		}(::std::make_index_sequence<sizeof...(Ts)>{});
	}

	constexpr void assign(const auto& other) requires (sizeof(type_traits::object_t<decltype(other)>) == basic::struct_size_v<base_type>)
	{
		::std::ranges::copy(::std::span(reinterpret_cast<byte_ptr_cst>(::std::addressof(other)), sizeof(other)), ::std::ranges::begin(_data));
	}

	constexpr self_type& operator=(const self_type&) = default;
	constexpr self_type& operator=(const storages::storage_structure auto& other)
		requires (sizeof(type_traits::object_t<decltype(other)>) == basic::struct_size_v<base_type>)
	{
		self_type::assign(other);
		return *this;
	}

	byte _data[basic::struct_size_v<base_type>]{};
};

using algorithm::to_string;

NGS_LIB_MODULE_END
