#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/buffer_target.h"

NGL_BEGIN

NGL_TARGET_BEGIN

//vertex
class NGS_API VertexArray;

//texture
class NGS_API Texture;

//shader
class NGS_API ShaderProgram;

//framebuffer
class NGS_API Framebuffer;

//renderbuffer
class NGS_API Renderbuffer;

NGS_END

class NGS_API  OpenGL : public Singleton<OpenGL> {
private:
	friend class  Singleton;
	OpenGL();
	~OpenGL();
public:
	//vertex
	targets::BufferTarget* const buffer_target;

	targets::VertexArray* const vertex_array;

	//texture
	targets::Texture* const texture;

	//shader
	targets::ShaderProgram* const shader;

	//framebuffer
	targets::Framebuffer* const framebuffer;

	//renderbuffer
	targets::Renderbuffer* const renderbuffer;
};

template<class>
struct NGS_API _get_target_function;

template<class _Object>
inline constexpr _get_target_function<_Object> get_target{};

template<class _Object>
void bind(_Object* object) { get_target<_Object>()->Select(object); }

template<class _Object>
void bind(_Object& object) { bind(&object); }

template<class _Object>
bool is_bind(_Object* object) { return get_target<_Object>()->IsState(object); }

template<class _Object>
bool is_bind(_Object& object) {return is_bind(&object);}

#define NGS_GL_GET_TARGET_FUNCTION(_target,_object,id)	\
template<std::derived_from<_object> _Object>			\
struct NGS_API _get_target_function<_Object> {			\
	_target* operator()()const noexcept {				\
		return OpenGL::I(). id;							\
	}													\
}														\
//

NGS_GL_GET_TARGET_FUNCTION(targets::BufferTarget, buffers::BufferObject, buffer_target);

NGL_END
