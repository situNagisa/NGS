#pragma once

#include "./defined.h"
#include "./delete_copy.h"

NGS_LIB_BEGIN
template<class _Derived>
class NGS_DLL_API singleton : public delete_copy {
	NGS_MPL_ENVIRON_BEGIN(singleton);
public:
	using singleton_type = _Derived;

	static singleton_type& instance() {
		static singleton_type instance;
		return instance;
	}
};

NGS_LIB_END