#pragma once

#include "NGS/nda/impl/opengl/defined.h"

NDA_IMPL_OPENGL_BEGIN

struct IDrawUnit {
	IDrawUnit(DisplayObject* display)
		: display(display)
	{}
	virtual void Render() {
		matrix
			.Scale(display->transform.scale)
			//.Rotation()
			.Translate(display->transform.offset);
	}

	DisplayObject* display = nullptr;
	matrix_t matrix = mla::identity_matrix_v<3, float>;
};

NDA_IMPL_OPENGL_END
