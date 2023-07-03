#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/stream.h"

NGS_BEGIN

class Constructor {
public:
	template<class T, class... Args>
	static void Construct_Place(T* block, Args&&... args) { new(block)T(std::forward<Args>(args)...); }

	template<class T, class... Args>
	static constexpr T Construct(Args&&... args) { return T(std::forward<Args>(args)...); }

	template<class T, class... Args>
	static T* Construct_Array(size_t count, Args&&... args) { return new T[count](std::forward<Args>(args)...); }


};

class Destructor {
public:
	template<class T>
	static void Destruct(T* block) { delete block; }

	template<class T>
	static void Destruct_Array(T* block) { delete[] block; }

	static void Destruct(std::ranges::random_access_range auto range) {
		for (auto& item : range)
			Destruct(item);
	}
};

class SegmentManager {

	struct ConstructorProxy {
		NGS_TYPE_DEFINE(ConstructorProxy, proxy);

		__proxy operator[](size_t n)const { return { size,id }; }

		size_t size = 1;
		std::string id = "";
	};
};

class Allocator : public Singleton<Allocator> {
public:
	struct AllocatedInfo {
		size_t count = 0;
		size_t size = 0;
		std::string id = "";
		std::string type_name = {};
		std::string function_name = {};
		size_t column = 0;
		size_t line = 0;

		operator std::string()const { return Format("%s%s %s", type_name.c_str(), count > 1 ? Format("[%d]", count).c_str() : "", id.c_str()); }
	};
private:
	friend class Singleton<Allocator>;
	Allocator() {
		NGS_LOGL(debug, "allocator init");
	}
	~Allocator() {
		NGS_LOGL(debug, "allocator destroy");
	}
public:

	void Show()const {
		NGS_PRINTL();
		NGS_PRINTL(TextColor::MAGENTA, "allocated memory:");
		size_t used = 0;
		for (auto& [block, info] : _allocated_info) {
			NGS_PRINTL(
				TextColor::GREEN, info, " ",
				TextColor::WHITE, (void*)block,
				TextColor::YELLOW, " [", info.size * info.count, "]",
				TextColor::WHITE, "bytes -- ",
				TextColor::CYAN, info.function_name,
				TextColor::WHITE, Format("[%d,%d]", info.line, info.column),
				TextColor::RESERT
			);
			used += info.size * info.count;
		}
		NGS_PRINTL(TextColor::MAGENTA, Format("used memory size:%d bytes", used));
		NGS_PRINTL();
	}

	template<class T>
	void Record_Allocate(T* block, size_t count = 1, std::string_view id = "unnamed", source_location source = source_location::current()) {
		auto& info = _allocated_info[block];
		info.count = count;
		info.size = sizeof(T);
		info.id = id;
		info.type_name = NGS_GET_TYPE_NAME(T);
		info.function_name = source.function_name();
		info.column = source.column();
		info.line = source.line();

		NGS_PRINTL(
			TextColor::WHITE, "allocated ",
			TextColor::YELLOW, info.size * info.count, "bytes ",
			TextColor::WHITE, "\taddress: ",
			(block ? TextColor::WHITE : TextColor::RED), (void*)block,
			TextColor::WHITE, "\ttype: ",
			TextColor::CYAN, info,
			TextColor::RESERT
		);
	}
	void Record_Free(void* block) {
		auto& info = _allocated_info[block];
		NGS_PRINTL(
			TextColor::WHITE, "freed     ",
			TextColor::GREEN, info.size * info.count, "bytes ",
			TextColor::WHITE, "\taddress: ",
			(block ? TextColor::WHITE : TextColor::RED), (void*)block,
			TextColor::WHITE, "\ttype: ",
			TextColor::CYAN, info,
			TextColor::RESERT
		);
		_allocated_info.erase(block);
	}
	size_t GetUsedBytes() const {
		size_t used = 0;
		for (auto& [block, info] : _allocated_info) {
			used += info.size * info.count;
		}
		return used;
	}
	const AllocatedInfo& GetAllocatedInfo(void* block)const { return _allocated_info.at(block); }
	auto begin()const { return _allocated_info.cbegin(); }
	auto end()const { return _allocated_info.cend(); }
private:

private:
	std::unordered_map<void_ptr, AllocatedInfo> _allocated_info = {};
};
namespace {
	//保证allocator在main函数之前初始化
	inline static auto& allocator = Allocator::I();
}


inline void MemorySet(void* dst, byte value, size_t size) { memset(dst, value, size); }

template<_NGS_CPT CUnsignedIntegral UINT>
constexpr void MemorySet(UINT* dst, UINT value, size_t size) {
	//#pragma omp parallel for
	for (int64 i = 0; i < size; i++)
		dst[i] = value;
}

inline void MemoryCopy(void* dst, void_ptr_cst src, size_t size) { memcpy(dst, src, size); }


inline void MemoryMove(void* dst, void_ptr_cst src, size_t size) { memmove(dst, src, size); }

//实现基础逻辑，交换整形数据（最大可达八字节，即unsigned long long)
template<_NGS_CPT CUnsignedIntegral UINT>
void MemorySwap(UINT& a, UINT& b) {
	a ^= b;
	b ^= a;
	a ^= b;
}
//实现n个整数类型的数据交换
template<size_t N, _NGS_CPT CUnsignedIntegral UINT>
void MemorySwap(UINT* a, UINT* b) {
	//可用OpenMP或模板For优化这个for循环
	for (size_t i = 0; i < N; i++) {
		MemorySwap(a[i], b[i]);
	}
}
//同上，支持动态填写size参数，缺点是不能用For模板进行优化循环
template<_NGS_CPT CUnsignedIntegral UINT>
void MemorySwap(UINT* a, UINT* b, size_t size) {
	for (size_t i = 0; i < size; i++) {
		MemorySwap(a[i], b[i]);
	}
}

//Different 不同类型约束，此次确保T不为void
//接口
template<CDifferentFrom<void> T>
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

template<_NGS_CPT CIntegral T>
inline void ByteInverse(T& p) { ByteInverse(byte_ptr(&p), sizeof(T)); }

#ifdef _MSC_VER
inline
::size_t SizeOf(void* block) { return _msize(block); }
#else
inline
::size_t SizeOf(void* block) { return 0; }
#endif

template<size_t _Count>
class NumberAllocator {
public:
	NGS_TYPE_DEFINE(BitSet<_Count>, bits);
public:

	int64 Allocate() {
		for (size_t i = 0; i < _Count; i++) {
			if (_numbers[i])continue;
			_numbers[i] = true;
			return i;
		}
		return -1;
	}
	void Free(size_t number) {
		_numbers[number] = false;
	}
	bool IsAllocated(size_t number) const {
		return _numbers[number];
	}
	bool IsFull()const {
		return typename __bits::type(_numbers) == __bits::Mask;
	}
private:

private:
	__bits _numbers = 0;

};

NGS_END