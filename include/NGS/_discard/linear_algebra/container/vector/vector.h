#pragma once

#include "./defined.h"
#include "./base.h"

NGS_MATH_LA_VECTOR_CONTAINER_BEGIN

template<traits::vectors::dimension_t _Dimension, class _ValueType, class = std::make_index_sequence<_Dimension>>
struct vector;

template<traits::vectors::dimension_t _Dimension, class _ValueType, size_t... _Index>
struct vector<_Dimension, _ValueType, std::index_sequence<_Index...>> : vector_container<vector<_Dimension, _ValueType>>
{
	NGS_MPL_ENVIRON(vector);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	constexpr static traits::vectors::dimension_t dimension = _Dimension;
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
		requires concepts::vectors::copyable<expression_type, decltype(v)>
	{
		adapters::vectors::copy(base_type::_derived(), NGS_PP_PERFECT_FORWARD(v));
	}

	using base_type::operator=;

	constexpr auto&& access(traits::vectors::index_t index) { return source[index]; }
	constexpr auto&& access(traits::vectors::index_t index)const { return source[index]; }

	constexpr void assign(const type_traits::index_type_identity_t<_Index, value_type>&... right)
	{
		((source[_Index] = right), ...);
	}

	/**
	 * \brief 给容器第i个元素赋值
	 * \param index
	 * \param value
	 * \note
	 *	若按照提供的概念，只需access返回的是个左值即可达到此函数的效果
	 *	但若是在常量求值语境中，上面这种方法会导致编译器调用旧的堆栈（根据编译错误信息得知，具体细节未知）
	 *	从而编译失败，故写此函数（若后续有更好的解决方案，可考虑删除此函数）
	 */
	constexpr void assign(traits::vectors::index_t index, const value_type& value)
	{
		source[index] = value;
	}
public:
	value_type source[dimension]{};
};

#if defined(__cpp_deduction_guides)

vector()->vector<0, int>;

template<class _First, std::convertible_to<_First>... _Rest>
vector(_First, _Rest...) -> vector<sizeof...(_Rest) + 1, _First>;

template<concepts::vectors::expression _E>
vector(_E) -> vector<adapters::vectors::static_dimension<_E>, traits::vectors::value_t<_E>>;

#endif

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

NGS_MATH_LA_VECTOR_CONTAINER_END