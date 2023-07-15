#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/buffer_target.h"

NGL_BEGIN

NGL_TARGET_BEGIN

//vertex
class VertexArray;

NGS_END

class OpenGL : public Singleton<OpenGL> {
private:
	friend class base;
	OpenGL();
public:

	//vertex
	targets::BufferTarget* buffer_target;

	targets::VertexArray* vertex_array;
};

NGL_END
