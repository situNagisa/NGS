﻿#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/context.h"
#include "NGL/gl/error.h"

NGLGL_BEGIN

_NGL_DECALRE_CONTEXT(VertexArray, GLuint) {
	VertexArrayContext() { glGenVertexArrays(1, &_handle); }
	~VertexArrayContext() { glDeleteVertexArrays(1, &_handle); _handle = 0; }
};

/**
 * @brief 记录顶点数组对象的状态
 *
 * 顶点数组（VAO）可以记录以下状态：
 * 1. 顶点缓冲区对象(ArrayBuffer)
 * 2. 索引缓冲区对象(ElementBuffer)
 * 3. 着色器程序对象(ShaderProgram)
 * 4. 纹理对象(Texture)
 * 5. 当前能活动的纹理单元(TextureUnit)
 * 6. RGB混合因子(RGBBlendFactor)
 * 7. Alpha混合因子(AlphaBlendFactor)
 * 8. Alpha混合目标因子(AlphaBlendFactor)
 * 9. RGB混合方程(BlendEquation)
 * 10. Alpha混合方程(BlendEquation)
 * 11. 深度测试函数(DepthFunc)
 * 12. 模板测试函数(StencilFunc)
 * 13. 模板测试操作(StencilOp)
 *
 * @note 你无法直接创建顶点数组对象,你只能使用命名空间`::ngs::ngl::gl::vector_array`实例来使用顶点数组对象
 */
_NGL_DECALRE_CURRENT(VertexArray) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR(VertexArray) { _NGL_CHECK(glBindVertexArray(context)); }
public:

};
_NGL_CURRENT_INSTANCE(vertex_array, VertexArray);

NGLGL_END

