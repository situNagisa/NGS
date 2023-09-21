#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/memory.h"


NGS_BEGIN

template<typename T>
T* new_(T* block, size_t count = 1, const source_location& source = source_location::current()) {
	Allocator::I().Record_Allocate(block, count, source);
	return block;
}


template<typename T>
void delete_(T* block) {
	Destructor::DESTRUCT(block);
	Allocator::I().Record_Free(block);
}


template<typename T>
void delete_array(T* block) {
	Destructor::DESTRUCT_ARRAY(block);
	Allocator::I().Record_Free(block);
}

NGS_END

#if NGS_BUILD_TYPE == NGS_DEBUG

#define NGS_NEW(ptr,...)											\
ptr = (__VA_ARGS__*)std::malloc(sizeof(__VA_ARGS__));				\
NGS_ASSERT(ptr,"nagisa new fail!");									\
_NGS Allocator::I().Record_Allocate((__VA_ARGS__*)ptr, 1, #ptr);	\
new(ptr)__VA_ARGS__													\
//
#define NGS_NEW_ARR(ptr,count,...)									\
ptr = (__VA_ARGS__*)std::malloc(sizeof(__VA_ARGS__) * (count));		\
NGS_ASSERT(ptr, "nagisa new array fail!");							\
_NGS Allocator::I().Record_Allocate((__VA_ARGS__*)ptr, (count), #ptr); \
new(ptr)__VA_ARGS__[(count)]										\
//

#define NGS_DELETE(block) _NGS delete_(block)
#define NGS_DELETE_ARR(block) _NGS delete_array(block)

#else

#define NGS_NEW(ptr,...) ptr = new __VA_ARGS__
#define NGS_NEW_ARR(ptr,count,...) ptr = new __VA_ARGS__[count]
#define NGS_DELETE(block) _NGS Destructor::DESTRUCT(block)
#define NGS_DELETE_ARR(block) _NGS Destructor::DESTRUCT_ARRAY(block)

#endif
