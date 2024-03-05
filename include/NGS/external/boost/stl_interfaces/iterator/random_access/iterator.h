#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Value, auto Dereference, auto Subtract, auto PlusAssign, class... Args>
struct random_access_iterator : basic_interface<random_access_iterator<Value, Dereference, Subtract, PlusAssign, Args...>, ::std::random_access_iterator_tag, Value>
{
	NGS_MPL_ENVIRON2(random_access_iterator, basic_interface<random_access_iterator<Value, Dereference, Subtract, PlusAssign, Args...>, ::std::random_access_iterator_tag, Value>);
public:
	using param_pack_type = ::std::tuple<Args...>;

	NGS_MPL_INHERIT_TYPE(difference_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);

	constexpr static auto dereference_functor = Dereference;
	static_assert(::std::invocable<decltype(dereference_functor), Args...>, "dereference_functor is not valid functor");

	constexpr static auto subtract_functor = Subtract;
	static_assert(::std::invocable<decltype(subtract_functor), const param_pack_type&, const param_pack_type&>, "subtract_functor is not valid functor");

	constexpr static auto plus_assign_functor = PlusAssign;
	static_assert(::std::invocable<decltype(plus_assign_functor), param_pack_type&, difference_type>, "plus_assign_functor is not valid functor");

	constexpr random_access_iterator() = default;
	constexpr random_access_iterator(auto&&... args) requires ::std::constructible_from<param_pack_type, decltype(args)...> && (sizeof...(Args) != 0)
		: _args(NGS_PP_PERFECT_FORWARD(args)...)
	{}

	constexpr decltype(auto) operator*()const { return ::std::apply(dereference_functor, _args); }
	constexpr difference_type operator-(const self_type& other)const { return subtract_functor(_args, other._args); }
	constexpr self_type& operator+=(difference_type n) { plus_assign_functor(_args, n); return *this; }

	constexpr auto&& param_pack() { return _args; }
	constexpr auto&& param_pack() const { return _args; }

	param_pack_type _args{};
};

NGS_LIB_MODULE_END
