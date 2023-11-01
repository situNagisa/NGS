#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

template<size_t _Dimension, class _ValueType, class = std::make_index_sequence<_Dimension>>
struct vector;

template<size_t _Dimension, class _ValueType, size_t... _Index>
struct vector<_Dimension, _ValueType, std::index_sequence<_Index...>>
	: vector_container<vector<_Dimension, _ValueType>>
{
	NGS_MPL_ENVIRON(vector);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	constexpr static size_t dimension = _Dimension;
	using value_type = _ValueType;

public:
	using base_type::base_type;
	/**
	 * \brief 默认初始化
	 * \note 此函数用于减缓智能提示压力
	 */
	constexpr vector() = default;

	constexpr vector(const type_traits::index_type_identity_t<_Index, value_type>&... right)
		: source{ right... }
	{}
	constexpr explicit(false) vector(auto&& v)
		requires functor::copyable<expression_type, decltype(v)>
	{
		functor::copy(base_type::_derived(), NGS_PP_PERFECT_FORWARD(v));
	}

	using base_type::operator=;

	constexpr auto&& access(size_t index)
	{
		return source[index];
	}
	constexpr auto&& access(size_t index)const
	{
		return source[index];
	}

	constexpr void assign(size_t index, functor::accessible auto&& right)
	{
		source[index] = static_cast<value_type>(functor::access(NGS_PP_PERFECT_FORWARD(right), index));
	}

	/**
	 * \brief
	 * \param index
	 * \param right
	 * \note 声明此函数是为了减缓智能提示压力
	 */
	constexpr void assign(size_t index, const value_type& right) { source[index] = right; }
	//constexpr void assign(size_t index, std::convertible_to<value_type> auto&& right)
	//{
	//	source[index] = static_cast<value_type>(right);
	//}
	constexpr void assign(const type_traits::index_type_identity_t<_Index, value_type>&... right)
	{
		((source[_Index] = right), ...);
	}
	//copy
	constexpr void assign(functor::accessible auto&& right)
	{
		((source[_Index] = static_cast<value_type>(functor::access(NGS_PP_PERFECT_FORWARD(right), _Index))), ...);
	}
public:
	value_type source[dimension]{};
};

vector()->vector<0, int>;

template<class _First, std::convertible_to<_First>... _Rest>
vector(_First, _Rest...) -> vector<sizeof...(_Rest) + 1, _First>;

template<functor::expression _E>
vector(_E) -> vector<functor::dimension<_E>, functor::value_t<_E>>;

template<class _ValueType>
using vector1 = vector<1, _ValueType>;
using vector1i = vector1<int>;
using vector1s = vector1<size_t>;
using vector1f = vector1<float>;
using vector1d = vector1<double>;

template<class _ValueType>
using vector2 = vector<2, _ValueType>;
using vector2i = vector2<int>;
using vector2s = vector2<size_t>;
using vector2f = vector2<float>;
using vector2d = vector2<double>;

template<class _ValueType>
using vector3 = vector<3, _ValueType>;
using vector3i = vector3<int>;
using vector3s = vector3<size_t>;
using vector3f = vector3<float>;
using vector3d = vector3<double>;

template<class _ValueType>
using vector4 = vector<4, _ValueType>;
using vector4i = vector4<int>;
using vector4s = vector4<size_t>;
using vector4f = vector4<float>;
using vector4d = vector4<double>;

NGS_MATH_VECTOR_END