//==========================================================================================================
// @file	:	NGS/NGS_Base
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:17:06
// @brief	:	
//==========================================================================================================
#pragma  once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"

NGS_BEGIN

template<class This>
class TypeDefined {
public:
	NGS_TYPE_DEFINE(This, this);
};

template<class Derived>
class Singleton {
public:
	static Derived& I() {
		static Derived instance;
		return instance;
	}
	static Derived* Instance() { return &I(); }
};

class DeleteCopy {
public:
	DeleteCopy() = default;
	DeleteCopy(const DeleteCopy&) = delete;
	DeleteCopy& operator=(const DeleteCopy&) = delete;
};

NGS_END