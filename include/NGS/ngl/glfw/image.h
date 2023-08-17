#pragma once

#include "NGS/ngl/glfw/defined.h"
#include "NGS/ngl/enum/cursor.h"

NGL_FW_BEGIN

class NGS_API  Image : DeleteCopy {
public:
	using self_type = Image;
public:
	Image(RGBA32* data,int width,int height)
		: _image({width,height,reinterpret_cast<unsigned char*>(data)})
	{}

	auto& GetImage() { return _image; }
	const auto& GetImage()const { return _image; }

private:
	GLFWimage _image;
};

NGL_FW_END
