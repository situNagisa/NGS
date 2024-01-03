#pragma once

#include "NGS/nsl/file/device_file.h"
#include "NGS/nsl/defined.h"

NSL_BEGIN

class FrameBuffer : public NSLDevice {
public:

	bool Open(const std::filesystem::path& path);

	bool IsOpened()const override { return _data; }
	void Close()override;

	size_t GetSize()const;
	size_t GetWidth()const;
	size_t GetHeight()const;

	ngs::void_ptr GetData() { return _screen; }
	ngs::void_ptr_cst GetData()const { return _screen; }

	template<typename _Color>
	_Color* GetData() { return reinterpret_cast<_Color*>(_screen); }
	template<typename _Color>
	const _Color* GetData()const { return reinterpret_cast<const _Color*>(_screen); }

private:
	DeviceFile _file = {};
	ngs::void_ptr _screen = nullptr;
};


NSL_END
