#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN
NGL_TARGET_BEGIN

template<class  _State>
class NGS_DLL_API TargetBase {
protected:
	using self_type = TargetBase;
public:
	using state_type = _State;

	void Select(_State& state) { Select(&state); }
	void Select(_State* state) { _current_state = state; }
	bool IsState(const _State& state) const { return IsState(&state); }
	bool IsState(const _State* state) const { return _current_state == state; }
	_State* GetCurrentState() { return _current_state; }

	bool operator==(const _State& state)const { return _current_state == &state; }

protected:
	_State* _current_state = nullptr;
};

template<class  _Derived, class  _State>
class NGS_DLL_API Target : public TargetBase<_State> {
	NGS_MPL_ENVIRON(Target);
public:
	using base = self_type;
	using state_type = _State;

	using base_type::Select;
	void Select(_State& state) { Select(&state); }
	void Select(_State* state) { base_type::Select(state); _Derived::_Select(state); };

};

NGS_END
NGL_END
