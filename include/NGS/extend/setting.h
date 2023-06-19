#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/memory.h"


NGS_BEGIN

template<typename T>
T* New(T* block, size_t count = 1, const source_location& source = source_location::current()) {
	Allocator::I().Record_Allocate(block, count, source);
	return block;
}


template<typename T>
void Delete(T* block) {
	Destructor::Destruct(block);
	Allocator::I().Record_Free(block);
}


template<typename T>
void Delete_Array(T* block) {
	Destructor::Destruct_Array(block);
	Allocator::I().Record_Free(block);
}

NGS_END

#if NGS_BUILD_TYPE == NGS_DEBUG

#define NGS_NEW(...)_NGS New(##__VA_ARGS__)
#define NGS_NEW_ARRAY(type,count,...) _NGS New(new type[count](##__VA_ARGS__),count)
#define NGS_DELETE(block) _NGS Delete(block)
#define NGS_DELETE_ARRAY(block) _NGS Delete_Array(block)

#else

#define NGS_NEW(...) (##__VA_ARGS__)
#define NGS_NEW_ARRAY(type,count,...) new type[count](##__VA_ARGS__)
#define NGS_DELETE(block) Destructor::Destruct(block)
#define NGS_DELETE_ARRAY(block) Destructor::Destruct_Array(block)

#endif
