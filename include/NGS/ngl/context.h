#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"

NGL_BEGIN

template<class _Handle = GLuint>
class Context : public DeleteCopy {
public:
	using handle_type = _Handle;

public:
	handle_type GetHandle()const { return _handle; }

	operator bool()const { return _handle; }
protected:
	handle_type _handle = {};
};

template<class _Context, class _Derived>
class Current : public DeleteCopy {
public:
	using context_type = _Context;


protected:
	NGS_TYPE_DEFINE(context_type, context);
	using base = Current<__context, _Derived>;
public:
	~Current() { _context = nullptr; }

	__context Create() { return {}; }

	void SetContextNull() {
		NGS_ASSERT(_stack.empty());
		_SetContextNull();
	}
	void SetContext(__context_ptr context) {
		NGS_ASSERT(_stack.empty());
		_SetContext(context);
	}
	void SetContext(__context_ref context) { SetContext(&context); }
	__context_ptr GetContext() { return _context; }
	__context_ptr GetContext()const { return _context; }

	void PushContext(__context_ptr context) {
		_stack.push(_context);
		_SetContext(context);
	}
	void PushContext(__context_ref context) { PushContext(&context); }
	void PopContext() {
		NGS_ASSERT(!_stack.empty());
		_SetContext(_stack.top());
		_stack.pop();
	}
	bool IsContext(__context_ptr_cst context)const { return _context == context; }
	bool IsContext(__context_ref_cst context)const { return IsContext(&context); }
private:
	void _SetContextNull() {
		_Derived::_SET_CURRENT_CONTEXT(0);
		_context = nullptr;
	}
	void _SetContext(__context_ptr context) {
		if (!context) {
			_SetContextNull();
			return;
		}
		_Derived::_SET_CURRENT_CONTEXT(context->GetHandle());
		_context = context;
	}
protected:
	__context_ptr _context = nullptr;
	std::stack<__context_ptr> _stack = {};
};
#define _NGL_DECALRE_CONTEXT(type,handle)		\
struct type##Context : Context<handle>			\
//

#define _NGL_DECALRE_CONTEXT_T(type,enum_type)	\
template<enum_type _E>							\
class type##Context : public _##type##Context{	\
public:											\
	constexpr static GLenum type = (GLenum)_E;	\
}												\
//

#define _NGL_DECALRE_CURRENT(type)				\
class type : public Current<type##Context, type>\
//

#define _NGL_DECLARE_CURRENT_T(type,enum_t)						\
_NGL_DECALRE_CONTEXT_T(type,enum_t);							\
template<enum_t _Type>											\
class type : public Current<type##Context<_Type>, type<_Type>>	\
//

#define _NGL_CURRENT_DEFAULT_CONSTRUCTOR(type)	\
private:										\
	friend class base;							\
	friend class Constructor;					\
	type() = default;							\
	static void _SET_CURRENT_CONTEXT(typename base::context_type::handle_type context)\
//

#define _NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(template_t)				\
using base = Current<template_t##Context<_Type>, template_t<_Type>>;\
constexpr static GLenum type = (GLenum)_Type;						\
_NGL_CURRENT_DEFAULT_CONSTRUCTOR(template_t)						\
//

#define _NGL_CURRENT_INSTANCE(id,current)		\
inline auto id = Constructor::Construct<current>()\
//

#define _NGL_SPECIALIZATION(template_t,template_enum,special_t,special_id)	\
using special_t##Context = template_t##Context<template_enum>;				\
using special_t = template_t<template_enum>;								\
_NGL_CURRENT_INSTANCE(special_id,special_t)									\
//


NGL_END
