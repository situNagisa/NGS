#pragma once

#include "NGS/nsl/media/frame_buffer.h"
#include "NGS/nsl/depend.h"

NSL_BEGIN

struct _FrameBufferData {
	fb_var_screeninfo var = {};
	fb_fix_screeninfo fix = {};
};

bool FrameBuffer::Open(const std::filesystem::path& path) {
	NGS_NEW(_data, _FrameBufferData)();
	auto& data = *reinterpret_cast<_FrameBufferData*>(_data);

	if (!_file.IsOpened() && !_file.Open(path)) {
		NGS_LOGFL(error, "open path %s fail!", path.string().c_str());
		goto err_new;
	}

	if (!_file.IOCtrl(FBIOGET_VSCREENINFO, &data.var)) {
		NGS_LOGL(error, "io ctrl var fail!");
		goto err_opened;
	}
	if (!_file.IOCtrl(FBIOGET_FSCREENINFO, &data.fix)) {
		NGS_LOGL(error, "io ctrl fix fail!");
		goto err_opened;
	}

	if (!(_screen = _file.MemoryMap(GetSize(), PROT_READ | PROT_WRITE, MAP_SHARED))) {
		NGS_LOGFL(error, "memory map fail!");
		goto err_opened;
	}
	NGS_LOGFL(debug, "successfully!");

	return true;

err_opened:;
	_file.Close();
err_new:;
	ngs::Delete(&data);
	_data = nullptr;

	return false;
}

NGS_HPP_INLINE void FrameBuffer::Close() {
	auto& data = *reinterpret_cast<_FrameBufferData*>(_data);

	_file.MemoryUnMap(_screen, GetSize());
	_file.Close();
	NGS_DELETE(&data);
	_data = nullptr;
}

NGS_HPP_INLINE size_t FrameBuffer::GetSize() const
{
	auto& data = *reinterpret_cast<_FrameBufferData*>(_data);
	return data.fix.line_length * data.var.yres;
}

NGS_HPP_INLINE size_t FrameBuffer::GetWidth() const
{
	auto& data = *reinterpret_cast<_FrameBufferData*>(_data);
	return data.var.xres;
}

NGS_HPP_INLINE size_t FrameBuffer::GetHeight() const
{
	auto& data = *reinterpret_cast<_FrameBufferData*>(_data);
	return data.var.yres;
}


NSL_END
