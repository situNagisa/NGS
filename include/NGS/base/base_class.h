//==========================================================================================================
// @file	:	NGS/NGS_Base
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:17:06
// @brief	:	
//==========================================================================================================
#pragma  once

#include "NGS/base/defined.h"

NGS_BEGIN

template<class  This>
class NGS_DLL_API  TypeDefined {
public:
	NGS_TYPE_DEFINE(This, this);
};

template<class  Derived>
class NGS_DLL_API  Singleton {
protected:
	using self_type = Singleton;
public:
	using base = self_type;

	static Derived& I() {
		static Derived instance;
		return instance;
	}
	static Derived* INSTANCE() { return &I(); }
};

class NGS_DLL_API  DeleteCopy {
public:
	DeleteCopy() = default;
	DeleteCopy(const DeleteCopy&) = delete;
	DeleteCopy& operator=(const DeleteCopy&) = delete;
};

NGS_END