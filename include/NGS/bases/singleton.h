#pragma once

#include "./defined.h"

NGS_BASES_BEGIN

template<class _Derived>
class NGS_DLL_API singleton {
protected:
	using self_type = singleton;
public:
	using singleton_type = _Derived;

	static singleton_type& instance() {
		static singleton_type instance;
		return instance;
	}
};

NGS_BASES_END