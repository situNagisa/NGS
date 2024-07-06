#pragma once

#include "../field.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class... Fields>
struct field_set
{
	NGS_PP_INJECT_BEGIN(field_set);
public:
	using field_tuple_type = ::std::tuple<Fields...>;

	template<::std::size_t I>
	constexpr static auto _recurse_check(auto&& fields_tuple, auto&& range)
	{
		if (!fields::check(::std::get<I>(NGS_PP_PERFECT_FORWARD(fields_tuple)), range))
			return false;
		if constexpr (I == ::std::tuple_size_v<type_traits::naked_t<decltype(fields_tuple)>> -1)
		{
			return true;
		}
		else
		{

			return self_type::template _recurse_check<I + 1>(NGS_PP_PERFECT_FORWARD(fields_tuple), NGS_PP_PERFECT_FORWARD(range));
		}
	}

	constexpr field_set() requires ::std::default_initializable<field_tuple_type> = default;
	constexpr explicit(sizeof...(Fields) == 0) field_set(auto&&... args) requires ::std::constructible_from<field_tuple_type, decltype(args)> : _fields(NGS_PP_PERFECT_FORWARD(args)...) {}

	constexpr static bool check(::std::ranges::input_range auto&& range)
		requires (fields::field<Fields, decltype(range)> && ...)
	{
		return self_type::template _recurse_check<0>(_fields, NGS_PP_PERFECT_FORWARD(range));
	}

	field_tuple_type _fields{};
};

NGS_LIB_MODULE_END