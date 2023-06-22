#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

#if NGS_COMPILER == NGS_GCC
#define NGS_GET_TYPE_NAME(type)		\
([]()->std::string					\
{									\
	const char* type_name = typeid(type).name();\
	char* name = abi::__cxa_demangle(type_name, nullptr, nullptr, nullptr);\
	if (!name) {\
		return type_name;\
	}\
	std::string result(name);\
	free(name);\
	return result;\
}())\
//
#else
#define NGS_GET_TYPE_NAME(type) ([]()->std::string { return typeid(type).name(); }())
#endif

template<class T>
struct _Check {
	static std::string name() { return NGS_GET_TYPE_NAME(T); }
};

//template<class T>
//struct _Check<const T> : _Check<T> {
//	static std::string name() { return "const " + _Check<T>::name(); }
//};


template<class T>
class TypeInfo {
public:
	TypeInfo() = default;

	operator std::string()const { return _Check<T>::name(); }
};

template<typename T>
inline std::string check_type(void) {
	return NGS_GET_TYPE_NAME(T);
}


NGS_END
