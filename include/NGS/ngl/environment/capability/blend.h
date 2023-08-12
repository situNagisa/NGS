#pragma once

#include "NGS/ngl/environment/capability/capability.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/enum/blend.h"

NGL_ENV_BEGIN

class Blend final : public ICapability {
public:
	void SetEquations(BlendEquations equations) { _equations = equations; }
	auto GetEquations()const { return _equations; }

	void SetSource(BlendFactors source) { _source = source; }
	auto GetSource()const { return _source; }

	void SetDestination(BlendFactors destination) { _destination = destination; }
	auto GetDestination()const { return _destination; }

	void Build() override {
		NGL_CHECK(glBlendFunc((GLenum)_source, (GLenum)_destination));
		NGL_CHECK(glBlendEquation((GLenum)_equations));
	}

	constexpr Capability GetDependCapability()const override{ return Capability::blend; }
public:
	BlendEquations _equations = BlendEquations::add;
	BlendFactors _source = BlendFactors::one;
	BlendFactors _destination = BlendFactors::zero;
};

NGL_ENV_END
