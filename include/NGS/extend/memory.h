#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/stream.h"

NGS_BEGIN

class Allocator : public Singleton<Allocator>, public TypeDefined<Allocator>
{
public:
	NGS_TYPE_DEFINE(size_t, size);
	NGS_TYPE_DEFINE(uint64, bytes);

#ifdef _DEBUG
	NGS_TYPE_DEFINE(std::type_info, std_info);

	struct TypeInfo {
		const std::type_info* std_info = nullptr;
		__size size = 0;
	};
	NGS_TYPE_DEFINE(TypeInfo, info);
	using __map = std::map<void*, __info>;
#endif

private:
	friend class Singleton<__this>;
	Allocator() {};
public:

	template<typename T = byte>
	T* Allocate(__size count = 1) {
		auto block = reinterpret_cast<T*>(malloc(count * sizeof(T)));
		_RecordAllocate(block, count);
		return block;
	}
	void Free(void* block, __size count = 1) {
		_RecordFree(block, count);
		free(block);
	}

	template<typename T, typename... Args>
	T* Construct(Args&&...args) {
		T* block = Allocate<T>();
		new(block)T(std::forward<Args>(args)...);
		return block;
	}

	template<typename T>
	void Destory(T* block) {
		if constexpr (std::is_same_v<T, void>) {
			_RecordFree(block);
			delete block;
			return;
		}
		else {
			block->~T();
			Free(block);
		}
	}

	template<typename T, typename... Args>
	T* ConstructArray(__size count, Args&&...args) {
		T* block = Allocate<T>(count);
		for (__size i = 0; i < count; i++)
			new(block + i)T(std::forward<Args>(args)...);

		return block;
	}

	template<typename T>
	void DestoryArray(T* block) {
		__size count = SizeOf(block) / sizeof(T);
		for (__size i = 0; i < count; i++)
			block[i].~T();
		Free(block, count);
	}

	template<typename T>
	T* New(T* block, __size count = 1) {
		_RecordAllocate(block, count);
		return block;
	}

	template<typename T>
	void Delete(T* block) { Destory(block); }

	template<typename T>
	void DeleteArray(T* block) { DestoryArray(block); }

	void Show() {
#if NGS_BUILD_TYPE == NGS_DEBUG
		nos.Trace(
			""
			"=============================="
			"\n已使用		%d bytes 内存"
			"\n相比上次增长了	%d bytes"
			"\n程序最大占用	%d bytes内存"
			"\n=============================\n"
			, _cur_used
			, (int64)_cur_used - _show_record
			, _max_used
		);
#endif  //_DEBUG
	}

private:
	template<class T>
	void _RecordAllocate(T* block, __size count) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		__info info;
		info.size = count * sizeof(T);
		info.std_info = &typeid(T);
		_map[block] = info;
		_cur_used += info.size;

		if (_cur_used > _max_used)_max_used = _cur_used;

		nos << Console::Color::WHITE << "申请"
			<< Console::Color::YELLOW << info.size << " bytes"
			<< Console::Color::WHITE << "内存，\t地址： "
			<< (block ? Console::Color::WHITE : Console::Color::RED) << (void*)block
			<< Console::Color::WHITE << "\t类型："
			<< Console::Color::CYAN << info.std_info->name()
			<< Console::Color::RESERT;
		;
		if (count != 1)
			nos.Trace("[%d]", count);
		nos.Trace("\n");
#endif
	}
	void _RecordFree(void* block, __size count = 1) {
#ifdef _DEBUG
		__info info = _map[block];
		_map.erase(block);
		_cur_used -= info.size;

		nos << Console::Color::WHITE << ("释放")
			<< Console::Color::GREEN << info.size << " bytes"
			<< Console::Color::WHITE << "内存，\t地址： "
			<< (block ? Console::Color::WHITE : Console::Color::RED) << (void*)block
			<< Console::Color::WHITE << "\t类型："
			<< Console::Color::CYAN << info.std_info->name()
			<< Console::Color::RESERT;
		;

		if (count != 1)
			nos.Trace("[%d]", count);
		nos.Trace("\n");
#endif
	}
#ifdef _DEBUG
	int64 _show_record = 0;
	__bytes _max_used = 0;
	__bytes _cur_used = 0;

	__map _map;
#endif
};


inline
void MemorySet(void* dst, byte value, size_t size) { memset(dst, value, size); }

template<_CPT UnsignedIntegral UINT>
constexpr
void
MemorySet(UINT* dst, UINT value, size_t size) {
	//#pragma omp parallel for
	for (int64 i = 0; i < size; i++)
		dst[i] = value;
}

inline
void
MemoryCopy(void* dst, void_ptr_cst src, size_t size) { memcpy(dst, src, size); }


inline
void
MemoryMove(void* dst, void_ptr_cst src, size_t size) { memmove(dst, src, size); }

//实现基础逻辑，交换整形数据（最大可达八字节，即unsigned long long)
template<_CPT UnsignedIntegral UINT>
void
MemorySwap(UINT& a, UINT& b) {
	a ^= b;
	b ^= a;
	a ^= b;
}
//实现n个整数类型的数据交换
template<size_t N, _CPT UnsignedIntegral UINT>
void
MemorySwap(UINT* a, UINT* b) {
	//可用OpenMP或模板For优化这个for循环
	for (size_t i = 0; i < N; i++) {
		MemorySwap(a[i], b[i]);
	}
}
//同上，支持动态填写size参数，缺点是不能用For模板进行优化循环
template<_CPT UnsignedIntegral UINT>
void
MemorySwap(UINT* a, UINT* b, size_t size) {
	for (size_t i = 0; i < size; i++) {
		MemorySwap(a[i], b[i]);
	}
}

//Different 不同类型约束，此次确保T不为void
//接口
template<DifferentFrom<void> T>
void MemorySwap(T* a, T* b) {
	constexpr auto rate = sizeof(T) / (sizeof(uint64));
	constexpr auto modulo = sizeof(T) % (sizeof(uint64));

	if constexpr (rate)
		//交换数据前rate * 8个字节
		MemorySwap<rate>(reinterpret_cast<uint64_ptr>(a), reinterpret_cast<uint64_ptr>(b));
	if constexpr (modulo)
		//交换剩下没交换的字节
		MemorySwap<modulo>(reinterpret_cast<byte_ptr>(a), reinterpret_cast<byte_ptr>(b));
}

inline void ByteInverse(byte_ptr p, size_t size) {
	for (size_t i = 0, len = size / 2; i < len; i++)
		MemorySwap(p + i, p + (size - 1 - i));
}

template<_CPT Integral T>
inline void ByteInverse(T& p) { ByteInverse(byte_ptr(&p), sizeof(T)); }

#ifdef _MSC_VER
inline
::size_t SizeOf(void* block) { return _msize(block); }
#else
inline
::size_t SizeOf(void* block) { return 0; }
#endif

template<size_t _COUNT>
class NumberAllocator {
public:

public:

	int64 Allocate() {
		for (size_t i = 0; i < _COUNT; i++) {
			if (Bits(_numbers, bit(i)))continue;
			Bits<true>(_numbers, bit(i));
			return i;
		}
		return -1;
	}
	void Free(size_t number) {
		Bits<false>(_numbers, number);
	}
	bool IsAllocated(size_t number) const {
		return Bits(_numbers, number);
	}
	bool IsFull()const {
		return _numbers == bit_max(_COUNT);
	}
private:

private:
	byte_<ByteOf(_COUNT) > _numbers = 0;

};

NGS_END