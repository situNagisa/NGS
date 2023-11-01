#pragma once

#include "NGS/ngl/environment/capability/capability.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/enum/blend.h"

NGL_ENV_BEGIN

class NGS_DLL_API Blend final : public ICapability {
public:
	void SetBlendMode(const BlendMode& blend) { _blend_mode = blend; }
	auto& GetBlendMode() { return _blend_mode; }
	const auto& GetBlendMode()const { return _blend_mode; }

	void SetEquations(BlendEquations equations) { _blend_mode.equation = equations; }
	auto GetEquations()const { return _blend_mode.equation; }

	void SetSource(BlendFactors source) { _blend_mode.src_factor = source; }
	auto GetSource()const { return _blend_mode.src_factor; }

	void SetDestination(BlendFactors destination) { _blend_mode.dst_factor = destination; }
	auto GetDestination()const { return _blend_mode.dst_factor; }

	virtual void Build() override {
		NGL_CHECK(glBlendFunc(static_cast<GLenum>(_blend_mode.src_factor), static_cast<GLenum>(_blend_mode.dst_factor)));
		NGL_CHECK(glBlendEquation(static_cast<GLenum>(_blend_mode.equation)));
	}

	constexpr virtual Capability GetDependCapability()const override { return Capability::blend; }
private:
	BlendMode _blend_mode = blend_mode::normal;
};

NGL_ENV_END
