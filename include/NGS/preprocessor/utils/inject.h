#pragma once

#define NGS_PP_INJECT_BEGIN(target)	\
protected:							\
	using self_type = target		\
//

#define NGS_PP_INJECT_EXPLICIT(target,...)			\
private:											\
	using base_type = __VA_ARGS__;					\
protected:											\
	using self_type = target						\
//

#define NGS_PP_INJECT(target) NGS_PP_INJECT_EXPLICIT(target, typename target::self_type)

#define NGS_PP_INHERIT_TYPE_EXPLICIT(id,...) using id = typename __VA_ARGS__::id
#define NGS_PP_INHERIT_VALUE_EXPLICIT(id,...) constexpr static auto id = __VA_ARGS__::id

#define NGS_PP_INHERIT_TYPE(id) NGS_PP_INHERIT_TYPE_EXPLICIT(id, base_type)
#define NGS_PP_INHERIT_VALUE(id) NGS_PP_INHERIT_VALUE_EXPLICIT(id, base_type)