#pragma once

#include "NGS/nsl/file/file.h"
#include "NGS/nsl/depend.h"

NSL_BEGIN

inline bool File::Access(__path_ref_cst path, AccessMode mode) {
	NGS_LOGFL(debug,"flag:%x", mode);
	return !access(path.string().c_str(), mode);
}


inline bool File::Open(__path_ref_cst path, OpenMode mode) {
	_path = path;
	NGS_LOGFL(debug, "flag:%x", mode);
	_fd = open(path.string().c_str(), mode);

	if (_fd < 0)
		NGS_LOGFL(error, "打开 %s 失败", path.string().c_str());
	else
		NGS_LOGFL(debug, "打开 %s 成功!", path.string().c_str());

	return _fd >= 0;
}

inline int File::Offset(int offset) { return lseek(_fd, offset, SEEK_CUR); }
inline int File::OffsetHead(int offset) { return lseek(_fd, offset, SEEK_SET); }
inline int File::OffsetTail(int offset) { return lseek(_fd, offset, SEEK_END); }

inline bool File::IsOpened() const { return _fd >= 0; }

inline void File::Close() {
	close(_fd);
	_path.clear();
	_fd = -1;
}

inline int File::Write(ngs::byte_ptr_cst data, size_t size) { return write(_fd, data, size); }
inline int File::Read(ngs::byte_ptr data, size_t size) { return read(_fd, data, size); }

inline ngs::void_ptr File::MemoryMap(ngs::void_ptr address, size_t length, int port, int flag, std::ptrdiff_t offset)
{
	auto map = mmap(address, length, port, flag, _fd, offset);
#if NGS_BUILD_TYPE == NGS_DEBUG
	if (map == MAP_FAILED)return nullptr;
#endif
	return map;
}

inline bool File::MemoryUnMap(ngs::void_ptr address, size_t size)
{
	return munmap(address, size) >= 0;
}


NSL_END
