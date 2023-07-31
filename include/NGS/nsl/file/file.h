#pragma once

#include "NGS/nsl/depend.h"
#include "NGS/nsl/defined.h"
#include "NGS/nsl/io/MultiplexIO.h"

NSL_BEGIN

class File : public ngs::DeleteCopy, public NSLObject {
	NGS_TYPE_DEFINE(std::filesystem::path, path);
public:
	NGS_FLAG(F_ACCESS_EXIST, FLAG_ANY);
	NGS_FLAG(F_ACCESS_EXE, 0);
	NGS_FLAG(F_ACCESS_WRITE, 1);
	NGS_FLAG(F_ACCESS_READ, 2);

	using AccessMode = uint32;

	NGS_FLAG(F_OPEN_READ_ONLY, FLAG_ANY);
	NGS_FLAG(F_OPEN_WRITE_ONLY, 0);
	NGS_FLAG(F_OPEN_READ_WRITE, 1);
	NGS_FLAG(F_OPEN_ACCMODE, F_OPEN_WRITE_ONLY | F_OPEN_READ_WRITE);
	NGS_FLAG(F_OPEN_CREAT, 6);
	NGS_FLAG(F_OPEN_EXCL, 7);
	NGS_FLAG(F_OPEN_TRUNC, 9);
	NGS_FLAG(F_OPEN_APPEND, 10);

	using OpenMode = uint32;

	static bool Access(__path_ref_cst path) {
		return Access(path, F_ACCESS_EXIST);
	}
	static bool Access(__path_ref_cst path, AccessMode flag);

	static constexpr OpenMode DefaultOpenMode() {
		return F_OPEN_READ_WRITE;
	}
public:

	File(__path_ref_cst path)
		: _path(path)
	{}
	File() = default;

	~File() {
		if (IsOpened())
			Close();
	}
	__path_ref_cst GetCurrentFilePath()const { return _path; }

	bool OpenDirectory(std::string_view dir, OpenMode mode) {
		_path = __path(dir) / _path;
		return Open(mode);
	}
	bool OpenDirectory(std::string_view dir) { return OpenDirectory(dir, DefaultOpenMode()); }
	bool Open() { return Open(DefaultOpenMode()); }
	bool Open(OpenMode mode) { return Open(_path, mode); }
	bool Open(__path_ref_cst path) { return Open(path, DefaultOpenMode()); }
	virtual bool Open(__path_ref_cst path, OpenMode mode);

	int Offset(int offset);
	int OffsetHead(int offset = 0);
	int OffsetTail(int offset = 0);

	bool IsOpened()const;
	void Close();

	template<size_t _N>
	int Write(const char(&data)[_N]) {
		return Write(std::string(data));
	}
	template<typename _Rng>
		requires std::ranges::contiguous_range<_Rng>&& std::ranges::sized_range<_Rng>&& std::convertible_to<std::ranges::range_value_t<_Rng>, ngs::byte>
	int Write(_Rng range) {
		return Write(std::ranges::cdata(range), std::ranges::size(range));
	}
	int Write(void_ptr_cst data, size_t size);
	int Read(void_ptr data, size_t size);

	template<typename... Args>
	int IOCtrlCode(ngs::uint32 request, Args&&... args) {
		//extern int ::ioctl(int, unsigned long int, ...);
		int result = ioctl(_fd, request, std::forward<Args>(args)...);
		return result;
	}
	template<typename... Args>
	bool IOCtrl(ngs::uint32 request, Args&&... args) {
		return IOCtrlCode(request, std::forward<Args>(args)...) >= 0;
	}

	ngs::void_ptr MemoryMap(size_t length, int port, int flag, std::ptrdiff_t offset = 0) { return MemoryMap(nullptr, length, port, flag, offset); }
	ngs::void_ptr MemoryMap(ngs::void_ptr address, size_t length, int port, int flag, std::ptrdiff_t offset = 0);

	template<typename T>
	static bool MemoryUnMap(T* address) { return MemoryUnMap(address, sizeof(T)); }
	static bool MemoryUnMap(ngs::void_ptr address, size_t size);
private:

private:
	__path _path = {};
	int _fd = -1;

	friend class MultIO;
};

NSL_END
