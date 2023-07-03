#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/utility.h"
NGS_BEGIN

#if NGS_COMPILER == NGS_GCC
#include <cxxabi.h> 
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

struct ParseIdFactor {
	static std::string bracket(const std::string& str) {
		return std::string(R"(()") + str + R"())";
	}
	template<std::convertible_to<std::string>... _Strings>
	static std::string or_(const std::string& string, const _Strings&... strings) {
		return bracket(string + (... + (R"(|)" + std::string(strings))));
	}
	static std::string before(const std::string& str, const std::string& before) {
		using namespace std::string_literals;
		return bracket(Format("%s(?=%s)", str.c_str(), before.c_str()));
	}
	static std::string after(const std::string& str, const std::string& after) {
		using namespace std::string_literals;
		return bracket(Format("(?<=%s)%s", after.c_str(), str.c_str()));
	}
	static std::string between(const std::string& before, const std::string& str, const std::string& after) {
		using namespace std::string_literals;
		return bracket(Format("(?<=%s)%s(?=%s)", before.c_str(), str.c_str(), after.c_str()));
	}

	inline static const std::string calling_convention = or_("__cdecl", "__stdcall", "__fastcall", "__vectorcall");
	inline static const std::string id = bracket(R"([a-zA-Z_]\w*)");
	inline static const std::string namespace_ = bracket(std::string{ R"(((\<\s*)?)" } + id + R"((\s*\>)?\s*::\s*)*)");
	inline static const std::string id_with_namespace = bracket(namespace_ + id);
	inline static const std::string type_qualifiers = bracket(R"((const)?\s*(volatile)?)");// R"((__ptr32|__ptr64|__restrict|__unaligned|__sptr|__uptr|__w64))";
	inline static const std::string operator_overloading = bracket(R"(operator\s*(((new|delete)\s*(\[\])?)|(((\&\&)|(\|\|)|(\>\>)|(\<\<)|(\-\-)|(\+\+)|(\-\>)|(\<\=\=\>)|\=|\+|\-|\*|\/|\!|\<|\>|\%|\^|\&|\|)\=?)|(\(\))|(\[\])))");


	inline static const std::string type = id_with_namespace;
	inline static const std::string parameter = bracket(Format(R"(\(\s*(%s(,%s)*)?\s*\))", type.c_str(), type.c_str()));// bracket(std::string{R"((\(\s*)"} + type + R"(\s*, \s*)" + type + R"(\s*) * ? \))");
	inline static const std::string function_name = bracket(namespace_ + or_(id, operator_overloading));

	static std::tuple<std::string, std::string, std::string, std::string> ParseFunction(const std::string& function) {
		std::string param{};
		{
			std::regex regex{parameter};
			std::smatch match;
			std::regex_search(function, match, regex);
			if (match.empty())return {};
			param = match.begin()->str();
		}
		std::string id_{};
		{
			std::regex regex{before(function_name, R"(\()")};
			std::smatch match;
			std::regex_search(function, match, regex);
			if (match.empty())return {};
			id_ = match.begin()->str();
		}
		std::string call{};
		{
			std::regex regex{calling_convention};
			std::smatch match;
			std::regex_search(function, match, regex);
			if (!match.empty())call = match.begin()->str();
		}
		std::string return_type{};
		if (!call.empty()) {
			std::regex regex{before(type + R"(\s*)", call)};
			std::smatch match;
			std::regex_search(function, match, regex);
			if (!match.empty())return_type = match.begin()->str();
		}

		return {
			call,
			return_type,
			id_,
			param
		};
	}
	static std::string GetFunctionName(const std::string& function) {
		std::string id_;
		std::regex regex{before(function_name, R"(\()")};
		std::smatch match;
		std::regex_search(function, match, regex);
		if (match.empty())return {};
		id_ = match.begin()->str();
		return id_;
	}
};


NGS_END
