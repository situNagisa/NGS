#pragma once

#include "../container.h"

NGS_MATH_VECTOR_BEGIN

template<size_t _Dimension,class _ValueType,class = std::make_index_sequence<_Dimension>>
struct vector;

template<size_t _Dimension,class _ValueType,size_t... _Index>
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
		: source({right...})
	{}

	using base_type::operator=;

	constexpr auto&& access(size_t index)
	{
		return source[index];
	}
	constexpr auto&& access(size_t index)const
	{
		return source[index];
	}

	constexpr void assign(size_t index,functor::accessible auto&& right)
	{
		source[index] = static_cast<value_type>(functor::access(NGS_PERFECT_FORWARD(right),index));
	}
	constexpr void assign(size_t index,const value_type& right)
	{
		source[index] = right;
	}
	constexpr void assign(const type_traits::index_type_identity_t<_Index,value_type>&... right)
	{
		((source[_Index] = right),...);
	}
	constexpr void assign(functor::accessible auto&& right)
	{
		((source[_Index] = static_cast<value_type>(functor::access(NGS_PERFECT_FORWARD(right), _Index))), ...);
	}
public:
	std::valarray<value_type> source{};
};

vector()->vector<0, int>;

template<class _First,std::convertible_to<_First>... _Rest>
vector(_First,_Rest...) -> vector<sizeof...(_Rest) + 1, _First>;

NGS_MATH_VECTOR_END