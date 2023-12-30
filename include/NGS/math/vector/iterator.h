#pragma once

#include "./defined.h"


NGS_LIB_BEGIN

namespace detail {
	template<class _T, auto _Dereference, auto _Subtract, auto _PlusAssign, class... _Args>
	struct iterator : ::boost::stl_interfaces::iterator_interface<
		iterator<_T, _Dereference, _Subtract, _PlusAssign, _Args...>
		, ::std::random_access_iterator_tag, _T>
	{
		using self_type = iterator;
		using base_type = ::boost::stl_interfaces::iterator_interface<self_type, ::std::random_access_iterator_tag, _T>;

		using param_pack_type = ::std::tuple<_Args...>;

		NGS_MPL_INHERIT_TYPE(difference_type, base_type);
		NGS_MPL_INHERIT_TYPE(value_type, base_type);

		constexpr static auto dereference_functor = _Dereference;
		static_assert(::std::invocable<type_traits::object_t<decltype(dereference_functor)>, _Args...>, "dereference_functor is not valid functor");

		constexpr static auto subtract_functor = _Subtract;
		static_assert(::std::invocable<type_traits::object_t<decltype(subtract_functor)>, const param_pack_type&, const param_pack_type&>, "subtract_functor is not valid functor");

		constexpr static auto plus_assign_functor = _PlusAssign;
		static_assert(::std::invocable<decltype(plus_assign_functor), param_pack_type&, difference_type>, "plus_assign_functor is not valid functor");

		constexpr iterator() = default;
		constexpr iterator(auto&&... args) requires ::std::is_constructible_v<param_pack_type, decltype(args)...>
			: args(NGS_PP_PERFECT_FORWARD(args)...)
		{}

		constexpr decltype(auto) operator*()const { return ::std::apply(dereference_functor, args); }
		constexpr difference_type operator-(const self_type& other)const { return subtract_functor(args, other.args); }
		constexpr self_type& operator+=(difference_type n) { plus_assign_functor(args, n); return *this; }

	public:
		param_pack_type args{};
	};

	inline constexpr auto random_access_subtract = [](auto&& left, auto&& right) {return ::std::get<0>(NGS_PP_PERFECT_FORWARD(left)) - ::std::get<0>(NGS_PP_PERFECT_FORWARD(right)); };
	inline constexpr auto random_access_plus_assign = [](auto& args, difference_t n) { ::std::get<0>(args) += n; };


}

template<class _T, auto _Dereference, class... _Args>
using vector_iterator = detail::iterator<_T, _Dereference, detail::random_access_subtract, detail::random_access_plus_assign, index_t, _Args...>;

struct adapter_sentinel
{
	constexpr adapter_sentinel() = default;
	constexpr explicit(false) adapter_sentinel(auto&&...) :adapter_sentinel() {}
	constexpr bool operator==(auto&&)const { return false; }
};

inline constexpr auto make_adapter_sentinel = [](auto&&...) { return adapter_sentinel{}; };

NGS_LIB_END