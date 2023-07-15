#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/base/object.h"

NGL_BEGIN
NGL_TARGET_BEGIN

template<class _Derived, class _State>
class Target {
public:
	using base = Target<_Derived, _State>;
	using state_type = _State;

	void Select(_State& state) { Select(&state); }
	void Select(_State* state) = { _current_state = state; _Derived::_Select(state); };
	bool IsState(const _State& state) const { return _current_state == &state; }

	bool operator==(const _State& state)const { return _current_state == &state; }

private:
	_State* _current_state = nullptr;
};

NGS_END
NGL_END
