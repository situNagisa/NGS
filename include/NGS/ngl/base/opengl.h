#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/buffer_target.h"

NGL_BEGIN

NGL_TARGET_BEGIN

//vertex
class VertexArray;

//texture
class Texture;

//shader
class ShaderProgram;

NGS_END

class OpenGL : public Singleton<OpenGL> {
private:
	friend class base;
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
};

NGL_END
