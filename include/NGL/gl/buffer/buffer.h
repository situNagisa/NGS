#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/context.h"
NGL_BEGIN

template<GLenum _Target>
class Buffer_Context {
public:
	Buffer_Context() {
		_New();
	}
	~Buffer_Context() {
		_Delete();
	}
	Buffer_Context(GLuint context)
		: _handle(context)
	{
		_Copy();
	}
	Buffer_Context(const Buffer_Context<_Target>& other)
		: _handle(other._handle)
	{
		_Copy();
	}


	Buffer_Context<_Target>& operator=(const Buffer_Context<_Target>& other) {
		_Copy();
		return *this;
	}
	operator bool()const { return _handle; }
	bool operator==(const Buffer_Context& other)const { return _handle == other._handle; }
	operator GLuint()const { return _handle; }
private:
	void _New() {
		NGS_Assert(!_handle);
		glGenBuffers(1, &_handle);
		NGS_Assert(!_count.contains(_handle) || !_count[_handle]);
		_count[_handle] = 1;
	}
	void _Copy() {
		if (!_handle)return;
		NGS_Assert(_count.contains(_handle) && _count[_handle]);
		_count[_handle]++;
	}
	void _Delete() {
		if (!_handle)return;
		NGS_Assert(_count.contains(_handle) && _count[_handle]);
		_count[_handle]--;
		if (!_count[_handle])glDeleteBuffers(1, &_handle);
	}
private:
	inline static std::unordered_map<GLuint, size_t> _count = {};
	GLuint _handle = 0;

	static_assert(Context<Buffer_Context<_Target>>);
};


template<GLenum _Target>
class Buffer_ContextManager : public GL_ContextManager<Buffer_Context<_Target>> {
	NGS_TYPE_DEFINE(Buffer_Context<_Target>, context);
public:
	static __context GetContext() {
		GLint context = 0;
		glGetIntegerv(_Target, &context);
		return context;
	}
	static void SetContext(__context context) { glBindBuffer(_Target, context); }
};

NGL_END
