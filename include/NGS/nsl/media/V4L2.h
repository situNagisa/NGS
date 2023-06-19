#pragma once

#include "NGS/nsl/file/device_file.h"
#include "NGS/nsl/defined.h"

NSL_BEGIN

class V4L2 : public NSLDevice {
public:

public:

	bool Open(const std::filesystem::path& path);
	bool IsOpened()const override;
	void Close();

	void LoadDeviceDescription();

	std::vector<ngs::PixelFormat> GetSupportPixelFormat()const;
	bool IsSupport(ngs::PixelFormat)const;

	void Update();

	bool Initialize();
	bool Initialize(size_t width, size_t height, ngs::PixelFormat format) {
		if (!SetFormat(width, height, format))return false;
		return Initialize();
	}
	bool Initialize(ngs::byte frameRate) {
		if (!SetFrameRate(frameRate))return false;
		return Initialize();
	}
	bool Initialize(size_t width, size_t height, ngs::PixelFormat format, ngs::byte frameRate) {
		if (!SetFormat(width, height, format))return false;
		if (!SetFrameRate(frameRate))return false;
		return Initialize();
	}

	bool SetFormat(size_t width, size_t height, ngs::PixelFormat format);
	bool SetFrameRate(ngs::byte frameRate);

	bool Read(ngs::void_ptr data);
	std::pair<ngs::byte_ptr, size_t> Read() {
		std::pair<ngs::byte_ptr, size_t> pair = {};
		auto& [data, size] = pair;
		size = GetFrameBufferSize();
		data = NGS_NEW_ARRAY(ngs::byte, size);
		Read(data);
		return pair;
	}

	const ngs::Point2s& GetSize()const;
	size_t GetFrameBufferSize()const;

	const size_t GetWidth()const { return GetSize().x; }
	const size_t GetHeight()const { return GetSize().y; }

private:

private:

};

NSL_END
