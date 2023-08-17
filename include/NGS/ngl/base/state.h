#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

struct NGS_API State : DeleteCopy {
	using state_type = State;

	State() = default;
	State(State&& other)
		: _context(other._context)
	{
		other._context = 0;
	}
	virtual ~State() = default;

	void RequiredUpdate() { _required_update = true; }
	virtual void Update() { _required_update = false; }

	context_t GetContext()const { return _context; }
protected:
	bool _required_update = false;
	context_t _context = 0;
};

NGL_END
