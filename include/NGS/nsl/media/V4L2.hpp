#pragma once

#include "NGS/nsl/media/V4L2.h"
#include "NGS/nsl/depend.h"

NSL_BEGIN

namespace ngs_linux {
	NGS_HPP_INLINE const std::unordered_map<ngs::uint32, ngs::PixelFormat> pixel_convert_map = {
		{V4L2_PIX_FMT_RGB332,ngs::PixelFormat::ARGB8},
		{V4L2_PIX_FMT_RGB555,ngs::PixelFormat::ARGB15},
		{V4L2_PIX_FMT_ARGB555,ngs::PixelFormat::ARGB15},
		{V4L2_PIX_FMT_RGB565,ngs::PixelFormat::ARGB16},
		{V4L2_PIX_FMT_RGB24,ngs::PixelFormat::ARGB24},
		{V4L2_PIX_FMT_RGB32,ngs::PixelFormat::ARGB32},

		{V4L2_PIX_FMT_MJPEG,ngs::PixelFormat::MJPEG},

		{V4L2_PIX_FMT_YUYV,ngs::PixelFormat::ARGB16},
	};
	NGS_HPP_INLINE ngs::PixelFormat Convert(ngs::uint32 format) {
		auto it = pixel_convert_map.find(format);
		NGS_LOGFL(debug, "convert format 0x%x", format);
		return it == pixel_convert_map.end() ? ngs::PixelFormat::unknown : it->second;
	}
	NGS_HPP_INLINE ngs::uint32 Convert(ngs::PixelFormat format) {
		for (auto& i : pixel_convert_map) {
			if (i.second == format)return i.first;
		}
		NGS_LOGFL(warning, "unknown pixel format");
		return 0;
	}
}

struct _V4l2Data {
	struct Format {
		ngs::PixelFormat format;
		ngs::byte description[32];
		std::vector<
			std::tuple<
			size_t, size_t,//width height
			std::vector<ngs::byte> //fps
			>
		> data;
	};
	DeviceFile device = {};
	v4l2_capability cap = {};
	std::vector<Format> descriptions = {};
	ngs::Point2s size = {};

	std::array<std::pair<ngs::void_ptr, size_t>, 4> buffers = {};
	v4l2_buffer* currentBuffer = nullptr;
};

NGS_HPP_INLINE bool V4L2::Open(const std::filesystem::path& path) {
	NGS_NEW(_data, _V4l2Data)();
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);

	if (!data.device.Open(path)) {
		NGS_LOGFL(error, "V4L2 can't open device file %s!", path.string().c_str());
		goto err;
	}
	if (!data.device.IOCtrl(VIDIOC_QUERYCAP, &data.cap)) {
		NGS_LOGFL(error, "V4L2 can't read capture!");
		return false;
	}
	if (!bit::get(data.cap.capabilities, V4L2_CAP_VIDEO_CAPTURE)) {
		NGS_LOGFL(error, "%s : No capture video device!", path.string().c_str());
		goto err;
	}
	NGS_LOGFL(debug, "open %s successfully", path.string().c_str());

	LoadDeviceDescription();

	return true;
err:;
	if (data.device.IsOpened())data.device.Close();

	NGS_DELETE(&data);
	_data = nullptr;
	return false;
}

NGS_HPP_INLINE bool V4L2::IsOpened() const { return _data; }

NGS_HPP_INLINE void V4L2::Close()
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);

	for (auto& cache : data.buffers) {
		data.device.MemoryUnMap(cache.first, cache.second);
	}

	v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (!data.device.IOCtrl(VIDIOC_STREAMOFF, &type)) {
		NGS_LOGFL(error, "close buffer stream fail!");
	}
	data.device.Close();

	ngs::Delete(&data);
	_data = nullptr;
}

NGS_HPP_INLINE void V4L2::LoadDeviceDescription() {
	NGS_LOGFL(debug, "load device's format descriptions!");
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);

	v4l2_fmtdesc description = {};

	v4l2_frmsizeenum frm_size = {};
	v4l2_frmivalenum frm_ival = {};

	frm_size.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	frm_ival.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	description.index++;
	while (data.device.IOCtrl(VIDIOC_ENUM_FMT, &description)) {
		frm_size.index = 0;
		frm_size.pixel_format = description.pixelformat;
		frm_ival.pixel_format = description.pixelformat;

		data.descriptions.push_back({});
		_V4l2Data::Format& format = data.descriptions.back();

		auto pix_fmt = ngs_linux::Convert(description.pixelformat);
		if (pix_fmt != ngs::PixelFormat::unknown)
			format.format = pix_fmt;
		else
			format.format = (ngs::PixelFormat)pix_fmt;
		//format.format = pix_fmt;

		std::memcpy(format.description, description.description, sizeof(description.description));

		NGS_LOGFL(debug, "format 0x%x description %s", format.format, format.description);

		while (data.device.IOCtrl(VIDIOC_ENUM_FRAMESIZES, &frm_size)) {
			frm_ival.index = 0;
			frm_ival.width = frm_size.discrete.width;
			frm_ival.height = frm_size.discrete.height;

			format.data.push_back({});
			auto& tuple = format.data.back();
			auto& [width, height, fps] = tuple;
			width = frm_size.discrete.width;
			height = frm_size.discrete.height;

			NGS_LOGFL(debug, "size< %d,%d >", width, height);

			while (data.device.IOCtrl(VIDIOC_ENUM_FRAMEINTERVALS, &frm_ival)) {
				fps.push_back(frm_ival.discrete.numerator);
				NGS_LOGFL(debug, "\tfps<%d>\n", fps.back());
				frm_ival.index++;
			}

			frm_size.index++;
		}
		description.index++;
	}
	NGS_LOGFL(debug, "descriptions %d", data.descriptions.size());
}

NGS_HPP_INLINE std::vector<ngs::PixelFormat> V4L2::GetSupportPixelFormat() const
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	std::vector<ngs::PixelFormat> formats;

	for (const auto& format : data.descriptions) {
		//if (format.format == ngs::PixelFormat::unknown)continue;
		formats.push_back(format.format);
	}

	return formats;
}

NGS_HPP_INLINE bool V4L2::IsSupport(ngs::PixelFormat f) const
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	std::vector<ngs::PixelFormat> formats;

	for (const auto& format : data.descriptions) {
		if (format.format == f)return true;
	}

	return false;
}

NGS_HPP_INLINE void V4L2::Update() {
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	if (!data.device.IOCtrl(VIDIOC_QBUF, data.currentBuffer)) {
		NGS_LOGFL(error, "queue buffer fail!");
		return;
	}
	//ngs::nos.Log("V4L2::Update", "dequeue buffer successfully!\n");
	v4l2_buffer& buffer = *data.currentBuffer;

	buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buffer.memory = V4L2_MEMORY_MMAP;
	// 从队列中取出一帧数据 
	if (!data.device.IOCtrl(VIDIOC_DQBUF, &buffer)) {
		NGS_LOGFL(error, "dequeue buffer fail!");
		return;
	}
	//ngs::nos.Log("V4L2::Update", "queue buffer successfully!\n");
}

NGS_HPP_INLINE bool V4L2::Initialize()
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);

	//初始化帧缓冲，申请内存映射
	{
		v4l2_requestbuffers requestBuffer = {};
		v4l2_buffer buffer = {};

		requestBuffer.count = data.buffers.max_size();
		requestBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		requestBuffer.memory = V4L2_MEMORY_MMAP;

		if (!data.device.IOCtrl(VIDIOC_REQBUFS, &requestBuffer)) {
			NGS_LOGFL(error, "allocate buffer fail!");
			return false;
		}

		buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer.memory = V4L2_MEMORY_MMAP;
		for (buffer.index = 0; buffer.index < data.buffers.max_size(); buffer.index++) {
			if (!data.device.IOCtrl(VIDIOC_QUERYBUF, &buffer)) {
				NGS_LOGFL(error, "allocate buffer fail!");
				return false;
			}
			auto& cache = data.buffers.at(buffer.index);
			cache.first = data.device.MemoryMap(buffer.length, PROT_READ | PROT_WRITE, MAP_SHARED, buffer.m.offset);
			cache.second = buffer.length;
			if (cache.first == MAP_FAILED) {
				NGS_LOGFL(error, "memory map error!");
				return false;
			}
		}
		NGS_LOGFL(debug, "memory map successfully!");

		for (buffer.index = 0; buffer.index < data.buffers.max_size(); buffer.index++)
		{
			if (!data.device.IOCtrl(VIDIOC_QBUF, &buffer)) {
				NGS_LOGFL(error, "[%d] queue buffer fail!", buffer.index);
				return false;
			}
		}
	}

	//开启摄像头采集
	{
		v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if (!data.device.IOCtrl(VIDIOC_STREAMON, &type)) {
			NGS_LOGFL(error, "open camera stream fail!");
			return false;
		}
	}

	//初始化当前指针，采集第一帧
	{
		NGS_NEW(data.currentBuffer, v4l2_buffer)();
		v4l2_buffer& buffer = *data.currentBuffer;

		buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer.memory = V4L2_MEMORY_MMAP;
		// 从队列中取出一帧数据 
		if (!data.device.IOCtrl(VIDIOC_DQBUF, &buffer)) {
			NGS_LOGFL(error, "dequeue buffer fail!");
			return false;
		}
	}

	return true;
}

NGS_HPP_INLINE bool V4L2::SetFormat(size_t width, size_t height, ngs::PixelFormat p)
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	v4l2_format fmt = {};
	ngs::uint32 pixel = 0;

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	fmt.fmt.pix.pixelformat = pixel = ngs_linux::Convert(p);
	if (!data.device.IOCtrl(VIDIOC_S_FMT, &fmt)) {
		NGS_LOGFL(error, "can't set frame format!");
		return false;
	}
	if (fmt.fmt.pix.pixelformat != pixel) {
		NGS_LOGFL(error, "the device doesn't support 0x%02x format!", p);
		return false;
	}

	data.size.x = fmt.fmt.pix.width;
	data.size.y = fmt.fmt.pix.height;
	NGS_LOGFL(debug, "video size %d,%d", data.size.x, data.size.y);
	return true;
}

NGS_HPP_INLINE bool V4L2::SetFrameRate(ngs::byte frameRate)
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	v4l2_streamparm streamParm = {};

	streamParm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (!data.device.IOCtrl(VIDIOC_G_PARM, &streamParm)) {
		NGS_LOGFL(error, "set frame rate fail!");
		return false;
	}

	if (!bit::get(streamParm.parm.capture.capability, V4L2_CAP_TIMEPERFRAME)) {
		NGS_LOGFL(warning, "the device doesn't support frame rate set!");
		return false;
	}

	streamParm.parm.capture.timeperframe.numerator = 1;
	streamParm.parm.capture.timeperframe.denominator = frameRate;

	if (!data.device.IOCtrl(VIDIOC_S_PARM, &streamParm)) {
		NGS_LOGFL(error, "set frame rate fail!");
		return false;
	}

	return true;
}

NGS_HPP_INLINE bool V4L2::Read(ngs::void_ptr ptr)
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	NGS_ASSERT(data.currentBuffer);
	v4l2_buffer buffer = *data.currentBuffer;

	//ngs::nos.Log("V4L2::Read", "size:%d\n", buffer.bytesused);
	auto& [buffer_ptr, size] = data.buffers.at(buffer.index);
	std::memcpy(ptr, buffer_ptr, buffer.bytesused);

	return true;
}

NGS_HPP_INLINE const ngs::Point2s& V4L2::GetSize() const
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	return data.size;
}

NGS_HPP_INLINE size_t V4L2::GetFrameBufferSize() const
{
	auto& data = *reinterpret_cast<_V4l2Data*>(_data);
	NGS_ASSERT(data.currentBuffer);
	return data.currentBuffer->bytesused;
}



NSL_END