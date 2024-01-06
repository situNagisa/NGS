#pragma once

#include "../tag.h"
#include "../operate.h"
#include "./vector.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class, extent_t _Extent, class = ::std::make_index_sequence<_Extent>>
	struct static_vector;

	template<class _T, extent_t _Extent, size_t... _Index>
	struct static_vector<_T, _Extent, ::std::index_sequence<_Index...>>
		: allow_adl_operator
		, NGS_MATH_VECTOR_TAG_NS::tag<NGS_MATH_VECTOR_TAG_NS::vector>
	{
		NGS_MPL_ENVIRON_BEGIN(static_vector);
	public:
		using value_type = _T;
		constexpr static auto extent = _Extent;

		constexpr static_vector() = default;
		constexpr explicit(extent <= 1) static_vector(const type_traits::index_type_identity_t<_Index, value_type>&... args) : _data{ args... } {}
		constexpr static_vector(const self_type&) = default;
		constexpr self_type& operator=(const self_type&) = default;

		constexpr explicit(false) static_vector(auto&& other)
			requires assignable_from<self_type, decltype(other)>
		{
			NGS_MATH_VECTOR_OPERATE_NS::assign(*this, NGS_PP_PERFECT_FORWARD(other));
		}
		constexpr self_type& operator=(auto&& other)
			requires assignable_from<self_type, decltype(other)>
		{
			NGS_MATH_VECTOR_OPERATE_NS::assign(*this, NGS_PP_PERFECT_FORWARD(other));

			return *this;
		}
		constexpr auto&& at(index_t index)
		{
			NGS_ASSERT(index < extent, "out of range!");
			return _data[index];
		}
		constexpr auto&& at(index_t index) const
		{
			NGS_ASSERT(index < extent, "out of range!");
			return _data[index];
		}

		constexpr auto&& operator[](index_t index) { return _data[index]; }
		constexpr auto&& operator[](index_t index) const { return _data[index]; }

		constexpr auto begin() { return static_cast<value_type*>(_data); }
		constexpr auto begin() const { return static_cast<const value_type*>(_data); }
		constexpr auto end() { return static_cast<value_type*>(_data) + extent; }
		constexpr auto end() const { return static_cast<const value_type*>(_data) + extent; }

		NGS_EXTERN_STL_RANGE_INPUT_AND_OUTPUT_ITERATOR();
	public:
		/// public is for non-type template parameter, should not access it
		value_type _data[extent]{};
	};
}

template<class _T, extent_t _Extent> requires (_Extent != dynamic_extent) && (_Extent != adapter_extent)
struct vector<_T, _Extent> : _detail::static_vector<_T, _Extent>
{
	NGS_MPL_ENVIRON2(vector, _detail::static_vector<_T, _Extent>);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END