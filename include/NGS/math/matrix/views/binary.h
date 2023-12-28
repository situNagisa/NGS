#pragma once

#include "../concept.h"
#include "../tag.h"
#include "../access.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept multipiable = input_matrix<_L> && input_matrix<_R> && vectors::maybe_same_extent<::std::ranges::range_value_t<_L>, _R>;

	template<class _L, class _R> requires multipiable<_L, _R>
	struct multiply_minor_view : vectors::basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<multiply_minor_view<_L, _R>>
	{
		using left_type = vectors::param_trait<_L>;
		using right_type = vectors::param_trait<_R>;

		constexpr static decltype(auto) dereference(index_t minor, typename left_type::const_pointer left, typename right_type::const_pointer right, index_t major)
		{
			return vectors::product_inner(NGS_LIB_NAME::major(*left, major), NGS_LIB_NAME::minor(*right, minor));
		}
		using value_type = type_traits::object_t<decltype(dereference(0, nullptr, nullptr, 0))>;
		using iterator = vectors::vector_iterator<value_type, dereference, typename left_type::const_pointer, typename right_type::const_pointer, index_t>;
		constexpr static auto extent = extent_v<::std::ranges::range_value_t<_R>>;

		constexpr explicit(false) multiply_minor_view(typename left_type::const_pointer left, typename right_type::const_pointer right, index_t major)
			: _left(left)
			, _right(right)
			, _major(major)
		{}

		constexpr auto begin()const { return iterator(0, _left, _right, _major); }
		constexpr auto end()const { return iterator(::std::ranges::size(NGS_LIB_NAME::major(*_right, 0)), _left, _right, _major); }

		NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

	public:
		typename left_type::const_pointer _left;
		typename right_type::const_pointer _right;
		index_t _major;
	};

	template<class _L, class _R> requires multipiable<_L, _R>
	struct multiply_major_view : basic_matrix, ::std::ranges::view_base, ::std::ranges::view_interface<multiply_minor_view<_L, _R>>
	{
		using left_type = vectors::param_trait<_L>;
		using right_type = vectors::param_trait<_R>;

		constexpr static decltype(auto) dereference(index_t major, typename left_type::const_pointer left, typename right_type::const_pointer right)
		{
			return multiply_minor_view<_L, _R>(left, right, major);
		}
		using value_type = type_traits::object_t<decltype(dereference(0, nullptr, nullptr))>;
		using iterator = vectors::vector_iterator<value_type, dereference, typename left_type::const_pointer, typename right_type::const_pointer>;
		constexpr static auto extent = extent_v<_L>;

		constexpr explicit(false) multiply_major_view(typename left_type::param left, typename right_type::param right)
			: _left(&left)
			, _right(&right)
		{}

		constexpr auto begin()const { return iterator(0, _left, _right); }
		constexpr auto end()const { return iterator(::std::ranges::size(*_left), _left, _right); }

		NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

	public:
		typename left_type::const_pointer _left;
		typename right_type::const_pointer _right;
	};
}

template<class _L, class _R> requires _detail::multipiable<_L, _R>
using multiply_view = _detail::multiply_major_view< _L, _R>;

template<class _L, class _R> requires _detail::multipiable<_L, _R>
constexpr auto multiply(_L&& left, _R&& right)
{
	return multiply_view<_L, _R>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_MODULE_END

NGS_LIB_BEGIN

namespace detail
{
	template<class _L, class _R>
	concept allow_multiply_functor =
		tag_matrix<_L> && tag_matrix<_R> &&
		scalar_matrix<_L> && scalar_matrix<_R> &&
		NGS_LIB_MODULE_NAME::_detail::multipiable<_L, _R>;
}

template<class _L, class _R> requires detail::allow_multiply_functor<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END