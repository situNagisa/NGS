#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/gl/state.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

class Blend : DeleteCopy {
public:
	Capabilities capability = Capabilities::blend;
private:
	friend class Constructor;
	Blend() = default;
public:
	void Func(BlendFactors src, BlendFactors dst);
	void FuncSeparate(BlendFactors srcRGB, BlendFactors dstRGB, BlendFactors srcAlpha, BlendFactors dstAlpha);
	void Equation(BlendEquations mode);
	void EquationSeparate(BlendEquations modeRGB, BlendEquations modeAlpha);
};
inline static auto blender = Constructor::Construct<Blend>();

NGLGL_END
