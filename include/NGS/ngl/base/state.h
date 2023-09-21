#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

struct NGS_API State : DeleteCopy {
protected:
	using self_type = State;
public:
	using state_type = self_type;

	State() = default;
	State(self_type&& other) noexcept
		: _context(other._context)
	{
		other._context = 0;
	}
	virtual ~State() = default;

	void RequiredUpdate() { _required_update = true; }
	virtual void Update() { _required_update = false; }

	context_t GetContext()const { return _context; }
protected:
	bool _required_update = true;
	context_t _context = 0;
};

NGL_END
