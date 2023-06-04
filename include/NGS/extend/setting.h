#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/memory.h"


NGS_BEGIN

template<typename T = void>
inline T* Malloc(size_t count) { return Allocator::I().Allocate<T>(count); }

inline
void Free(void* block) { Allocator::I().Free(block); }



template<typename T>
T* New(T* block, size_t count = 1) { return Allocator::I().New(block, count); }


template<typename T>
void Delete(T* block) { Allocator::I().Delete(block); }


template<typename T>
void DeleteArray(T* block) { Allocator::I().DeleteArray(block); }

NGS_END