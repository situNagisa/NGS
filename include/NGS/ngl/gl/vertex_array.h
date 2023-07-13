#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl/vertex.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN


_NGL_DECALRE_CONTEXT(VertexArray, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { glGenVertexArrays(1, &handle); }
	static void _DESTROY(handle_type & handle) { glDeleteVertexArrays(1, &handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(VertexArray);
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
	void Enable(int index) { _NGL_CHECK(glEnableVertexAttribArray(index)); }
	void Disable(int index) { _NGL_CHECK(glDisableVertexAttribArray(index)); }

	void SetAttribPointer(size_t index, size_t count, size_t offset, int type, int step, bool normalized = false) {
		_NGL_CHECK(glVertexAttribPointer(index, count, type, normalized, step, (void_ptr_cst)offset));
	}
	template<CTemplateFrom<gl::vertex> _Layout>
	void SetAttribPointer(bool normalized = false, bool enable = true) {
		using lay = _Layout;
		for (size_t i = 0; i < lay::count; i++) {
			SetAttribPointer(i, lay::counts[i], lay::offsets[i], lay::tv_bitmaps[i], lay::size, normalized);
			if (enable)Enable(i);
		}
	}
	template<class _Element, size_t _L0, size_t... _LN>
	void SetAttribPointer(bool normalized = false, bool enable = true) {
		SetAttribPointer<vertex_c<_Element, _L0, _LN...>>(normalized, enable);
	}
	template<CTemplateFrom<layout> _LayoutUnit, CTemplateFrom<layout>... _LayoutUnits>
	void SetAttribPointer(bool normalized = false, bool enable = true) {
		SetAttribPointer<vertex<_LayoutUnit, _LayoutUnits...>>(normalized, enable);
	}

	void DrawElements(ElementDrawMode mode, size_t count, GLenum type_, size_t offset = 0) { _NGL_CHECK(glDrawElements((GLenum)mode, count, type_, (void_ptr_cst)offset)); }
	template<CSameAsAny<uint8, uint16, uint32> _T>
	void DrawElements(ElementDrawMode mode, size_t count, size_t offset = 0) { DrawElements(mode, count, gl_convert<_T>, offset); }
	void DrawArrays(DrawMode mode, size_t offset, size_t count) { _NGL_CHECK(glDrawArrays((GLenum)mode, offset, count)); }

#define DEFINE_DRAW_ELEMENTS(id,mode)				\
	template<CSameAsAny<uint8, uint16, uint32> _T>\
	void Draw##id(size_t count, size_t offset = 0) { DrawElements<_T>(mode, count, offset); }\
//

	DEFINE_DRAW_ELEMENTS(Points, ElementDrawMode::points);
	DEFINE_DRAW_ELEMENTS(Lines, ElementDrawMode::lines);
	DEFINE_DRAW_ELEMENTS(LineStrip, ElementDrawMode::line_strip);
	DEFINE_DRAW_ELEMENTS(LineLoop, ElementDrawMode::line_loop);
	DEFINE_DRAW_ELEMENTS(Triangles, ElementDrawMode::triangles);
	DEFINE_DRAW_ELEMENTS(TriangleStrip, ElementDrawMode::triangle_strip);
	DEFINE_DRAW_ELEMENTS(TriangleFan, ElementDrawMode::triangle_fan);
	DEFINE_DRAW_ELEMENTS(Patches, ElementDrawMode::patches);
#undef DEFINE_DRAW_ELEMENTS


};
_NGL_CURRENT_INSTANCE(vertex_array, VertexArray);

NGLGL_END

