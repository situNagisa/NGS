#pragma once

#include "./variable.h"
#include "./struct.h"
#include "../storage.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace  _detail
{
	template<class T>
	struct storage_constructor_param { using type = T; };
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
	storage(const _detail::storage_constructor_param_t<Ts>&... data) requires (::std::copyable<_detail::storage_constructor_param_t<Ts>> && ...)
	{
		[&]<::std::size_t... Index>(::std::index_sequence<Index...>){
			((storages::get<Index>(*this) = data), ...);
		}(::std::make_index_sequence<sizeof...(Ts)>{});
	}

	byte _data[basic::struct_size_v<base_type>]{};
};

using algorithm::to_string;

NGS_LIB_MODULE_END
