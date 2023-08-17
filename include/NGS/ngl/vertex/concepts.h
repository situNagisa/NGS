#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/vertex/vertex_format.h"
#include "NGS/ngl/vertex/trait.h"

NGS_BEGIN
NGS_CONCEPT

template<class  T, class  _ElementType = void>
concept CAttrib = std::convertible_to<T, typename ngl::tag::Attrib<_ElementType>::type>;

/**
 * @brief 属性的范围，满足以下条件之一：
 * 1）一个指针，指向类型为`_AttribElementType`
 * 2）一个前向范围，其元素类型可转换为`_AttribElementType`（当`_AttribElementType`不为`void`时）
 *
 * @tparam T
 * @tparam _ElementType 默认值为void，表示不限制元素类型
 */
template<class  T, class  _ElementType = void>
concept CAttribRange =
(std::is_pointer_v<T> && std::convertible_to<T, typename ngl::trait::range_t<ngl::tag::Attrib<_ElementType>>>) // 指针
|| (std::ranges::forward_range<T> && (std::same_as<_ElementType, void> || std::convertible_to<std::ranges::range_value_t<T>, typename ngl::tag::Attrib<_ElementType>::type>)); // 范围

/**
 * @brief 顶点缓存，满足以下条件之一：
 * 1）一个指针，指向类型为`_BufferElementType`
 * 2）一个前向范围，其元素类型可转换为`_BufferElementType`（当`_BufferElementType`不为`void`时）
 *
 * @tparam T
 * @tparam _ElementType
 */
template<class  T, class  _ElementType = void>
concept CVertexBuffer =
(std::is_pointer_v<T> && std::convertible_to<T, typename ngl::tag::Buffer<_ElementType>::type>) ||
(std::ranges::forward_range<T> && (std::same_as<_ElementType, void> || std::convertible_to<std::ranges::range_value_t<T>, typename ngl::tag::Buffer<_ElementType>::element_type>));

/**
 * @brief 缓存的范围，满足以下条件之一：
 * 1）一个指针，其指向的类型满足概念`CVertexBuffer`
 * 2）一个前向范围，其元素类型满足概念`CVertexBuffer`
 *
 * @see `CVertexBuffer`
 *
 * @tparam T
 * @tparam _ElementType 默认值为`void`，表示不限制元素类型
 *
 */
template<class  T, class  _ElementType = void>
concept CBufferRange =
(std::is_pointer_v<T> && CVertexBuffer<std::remove_pointer_t<T>, _ElementType>) ||
(std::ranges::forward_range<T> && (CVertexBuffer<std::ranges::range_value_t<T>, _ElementType>));


/**
 * @brief 顶点范围，满足以下条件之一：
 * 1）一个指针，指向类型满足概念`CBufferRange`
 * 2）一个前向范围，元素类型满足概念`CBufferRange`
 *
 * @see `CBufferRange`
 *
 * @tparam T
 * @tparam _BufferElementType 默认值为`void`，表示不限制元素类型
 */
template<class  T, class  _ElementType = void>
concept CVertexRange =
(std::is_pointer_v<T> && CBufferRange<std::remove_pointer_t<T>, _ElementType>) ||
(std::ranges::forward_range<T> && CBufferRange<std::ranges::range_value_t<T>, _ElementType>);

NGS_END
NGS_END
